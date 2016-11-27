#include "foundation/algorithm/iconsistent.h"
#include "foundation/util/idicttypes.h"
#include "foundation/util/iarraytypes.h"


/* the consistent destructor */
void iconsistent_destructor(const struct imeta *meta, iptr o) {
    iconsistent *c = icast(iconsistent, o);
    irefdelete(c->circle);
    irefdelete(c->elems);
}

/* make a empty iconsistent */
iconsistent *iconsistentmake(size_t capacity, size_t replicas) {
    iconsistent *c = irefnew(iconsistent);
    c->numberofreplicas = replicas;
    c->circle = idictmake(capacity);
    c->elems = idictmake(capacity);
    return c;
}
    
/* the element-size in circle */
size_t iconsistentsize(const iconsistent *c) {
    return idictsize(c->elems);
}

/* make a replicas-key */
istring *_iconsistent_key_n(iconsistent *c, istring *ele, int index) {
    return istringformat("%V|@@[%i]", ele, index);
}
   
/* add ele to c in span: replicasspan with numberofreplicas */
void iconsistentadd(iconsistent *c, istring *ele) {
    istring *key;
    
    for (int i=0; i<c->numberofreplicas; ++i) {
        key = _iconsistent_key_n(c, ele, i);
        idictadd_u64_istring(c->circle, iconsistenthashof(c, key), key);
        irefdelete(key);
    }
    idictadd_istring_ibool(c->elems, ele, iiok);
}

/* remove ele from c in span */
void iconsistentremove(iconsistent *c, istring *ele) {
    istring *key;
    
    for (int i=0; i<c->numberofreplicas; ++i) {
        key = _iconsistent_key_n(c, ele, i);
        idictremove_u64(c->circle, iconsistenthashof(c, key));
        irefdelete(key);
    }
    idictremove_istring(c->elems, ele);
}

int _iarray_range_search(iarray *elems, istring* key) {
    irangearray(elems, istring*,
                if (istringcompare(__value, key) == 0) {
                    return iiok;
                }
                );
    return iino;
}

/* set the circle to elems: remove all not in elems, add all in elems*/
/* iarray<istring*> */
void iconsistentset(iconsistent *c, iarray* elems) {
    const iarray * keys = idictkeys(c->elems);
    istring *skey;
    
    /* remove ele in members but not in elems */
    irangearray(keys, idictentry*,
                skey = ivarcast(__value->key, istring*);
                if (!_iarray_range_search(elems, skey)) {
                    iconsistentremove(c, skey);
                }
                );
    
    /* add elems to members */
    irangearray(elems, istring*,
                if (!idicthas_istring(c->elems, __value)) {
                    iconsistentadd(c, __value);
                }
                );
}

/* the index of elem-key ==> hashcode */
static uint64_t _iconsistent_key(const iconsistent *c, int index) {
    const iarray* sortedkeys = idictkeys(c->circle);
    idictentry *entry = iarrayof(sortedkeys, idictentry*, index);
    return ivarcast(entry->key, uint64_t);
}

/* the index of elem-key ==> skey */
static istring* _iconsistent_value(const iconsistent *c, int index) {
    const iarray* sortedkeys = idictkeys(c->circle);
    idictentry *entry = iarrayof(sortedkeys, idictentry*, index);
    return ivarcast(entry->value, istring*);
}

/* closed ele for key */
istring* iconsistentindexingof(const iconsistent *c, istring *key) {
    if (idictsize(c->circle) == 0) {
        return NULL;
    }
    int index = iconsistentindexing(c, key);
    return _iconsistent_value(c, index);
}

/* closed index for key */
int iconsistentindexing(const iconsistent *c, istring *key) {
    ivar *keyvar = ivarmakeu64(iconsistenthashof(c, key));
    idictentry entry = {.key=keyvar};
    const iarray* sortedkeys = idictkeys(c->circle);
    int index = iarraybinaryindexing(sortedkeys, 0, iarraylen(sortedkeys), &entry);
    irefdelete(keyvar);
    if (index >= iarraylen(sortedkeys)) {
        index = 0;
    }
    return index;
}

/* closest index for key then next n key will return */
iarray* iconsistentsearch(const iconsistent *c, istring *key, size_t n) {
    iarray* closest = iarraymakeiref(8);
    istring *skey;
    size_t nc = idictsize(c->circle);
    int start;
    int i;
    
    do {
        if (nc == 0) {
            break;
        }
        n = imin(n, nc);
        /* the first one */
        start = iconsistentindexing(c, key);
        skey = _iconsistent_value(c, start);
        iarrayadd(closest, &skey);
        if (iarraylen(closest) == n) {
            break;
        }
        
        /* the next left ones */
        for (i = start + 1; i != start; ++i) {
            if (i >= nc) {
                i = 0;
            }
            skey = _iconsistent_value(c, start);
            if (_iarray_range_search(closest, skey) == iino) {
                iarrayadd(closest, &skey);
            }
            if (iarraylen(closest) == n) {
                break;
            }
        }
        break;
    }while(0);
    
    /* no-indexing key */
    if (iarraylen(closest)==0) {
        irefdelete(closest);
    }
    return closest;
}

/* the hash-code-for key */
uint64_t iconsistenthashof(const iconsistent *c, istring *key) {
    return istringhashcode(key)%INT32_MAX;
}

/* the circle-size */
size_t iconsistentcount(const iconsistent *c) {
    return idictsize(c->circle);
}

/* the circle-hashcode at */
uint64_t iconsistentcodeat(const iconsistent *c, int index) {
    return _iconsistent_key(c, index);
}

/* the circle-value at */
istring *iconsistentvalueat(const iconsistent *c, int index) {
    return _iconsistent_value(c, index);
}
