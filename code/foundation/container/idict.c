#include "foundation/container/idict.h"
#include "foundation/util/iarraytypes.h"
#include "foundation/memory/imemory.h"

/* make a entry with key */
idictentry* idictentrymake(ivar *key) {
    idictentry *entry = irefnew(idictentry);
    entry->indexkey = kindex_invalid;
    entry->indexvalue = kindex_invalid;
    iassign(entry->key, key);
    return entry;
}

/* get a key from entry */
ivar *idictentrykey(const idictentry *e) {
    return e->key;
}

/* get a value from entry */
ivar *idictentryvalue(const idictentry *e) {
    return e->value;
}

/* set a value for entry */
void idictentysetvalue(idictentry *e, ivar *value) {
    iassign(e->value, value);
}

/* release all the resources with entry */
void idictentry_destructor(const struct imeta *meta, iptr o) {
    idictentry *entry = icast(idictentry, o);
    irefdelete(entry->key);
    irefdelete(entry->value);
}

/* the same as hash on key */
uint64_t idictentry_hash(const struct imeta *meta, iconstptr o) {
    idictentry *entry = icast(idictentry, o);
    return ivarhashcode(entry->key);
}

/* the meta assign */
void idictentry_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    idictentry *dentry = icast(idictentry, dst);
    idictentry *sentry = icast(idictentry, src);
    iassign(dentry->key, sentry->key);
    iassign(dentry->value, sentry->value);
}

/* the same as compare on key */
int idictentry_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    idictentry *lentry = icast(idictentry, lfs);
    idictentry *rentry = icast(idictentry, rfs);
    return ivarcompare(lentry->key, rentry->key);
}

/* private-data for idict */
typedef struct idict_private {
    size_t collides;
} idict_private;

/* index tracing for key-array */
void _irefarray_index_change_forkey(iptr x, iarray *arr, iref *ref, int index) {
    idictentry* entry = icast(idictentry, ref);
    if (entry) {
        entry->indexkey = index;
    }
}

/* index tracing for key-array */
static irefarrayentry _idictenty_array_forkey = {
    .indexchange = _irefarray_index_change_forkey
};

/* make a capacity of idictentry array for keys */
iarray *_idictentryarraymake_forkey(idict *d, size_t capacity) {
    return iarraymakeirefwithentry(capacity, &_idictenty_array_forkey);
}

/* index tracing for key-array */
void _irefarray_index_change_forvalue(iptr x, iarray *arr, iref *ref, int index) {
    idictentry* entry = icast(idictentry, ref);
    if (entry) {
        entry->indexvalue = index;
    }
}

/* index tracing for key-array */
static irefarrayentry _idictenty_array_forvalue = {
    .indexchange =_irefarray_index_change_forvalue
};

/* make a capacity of idictentry array for values */
iarray *_idictentryarraymake_forvalue(idict *d, size_t capacity) {
    return iarraymakeirefwithentry(capacity, &_idictenty_array_forvalue);
}

/* find in idictentry-array for key */
int _idictentryindexof(const idict *d, iarray *arr, const ivar *key) {
    int index = kindex_invalid;
    icheckret(arr, index);
    icheckret(key, index);
    /* temp val */
    idictentry *entry = irefnew(idictentry);
    iassign(entry->key, (ivar*)key);
    /* search and remove */
    if (iflag_is(d->flag, EnumDictFlag_NotSortingKeys)) {
        irangearray(arr, idictentry*,
                    if (idictentry_compare(imetaof(idictentry), __value, entry) == 0) {
                        index = __key;
                        break;
                    }
                    );    
    } else {
        index = iarraybinarysearch(arr, 0, iarraylen(arr), &entry);
    }
    /* free temp */
    irefdelete(entry);
    return index;
}

/* remove the right-key in idictentry-array */
int _idictentryremove(const idict *d, iarray *arr, const ivar *key) {
    /* search and remove */
    int index = _idictentryindexof(d, arr, key);
    if (index != kindex_invalid) {
        iarrayremove(arr, index);
    }
    return index;
}

/* add the entry to idictentry-array */
void _idictentryadd(const idict *d, iarray *arr, idictentry *entry) {
    if (iflag_is(d->flag, EnumDictFlag_NotSortingKeys)) {
        iarrayadd(arr, &entry);
    } else {
        iarraybinaryinsert(arr, 0, iarraylen(arr), &entry);
    }
}

/* get the idictentry of value in arr */
idictentry* _idictentryof(const idict *d, iarray *arr, const ivar *key) {
    /* search and remove */
    int index = _idictentryindexof(d, arr, key);
    if (index != kindex_invalid) {
        return iarrayof(arr, idictentry*, index);
    }
    return NULL;
}

/* private size protocol */
size_t _idictcapacity(const idict *d) {
    return iarraycapacity(d->values);
}

/* private size protocol */
size_t _idictnewcapacity(const idict *d) {
    return imin(_idictcapacity(d) * 2, INT32_MAX-1);
}

/* private size protocol */
size_t _idictnewshrinkcapacity(const idict *d) {
    return imax(_idictcapacity(d) / 2, 1);
}

/* raw-index in dict-value-array */
int _idictkeyindex(const idict *d, const ivar *key) {
    uint64_t hash = ivarhashcode(key);
    return hash % _idictcapacity(d);
}

/* raw-dictentry-array in dict */
iarray *_idictentryarrayof(const idict *d, const ivar *key) {
    int index = _idictkeyindex(d, key);
    return icast(iarray, iarrayof(d->values, irefptr, index));
}

/* rehashing-indexing a entry */
static void _idictrehashingentry(idict *d, idictentry* entry) {
    iarray* indexentrys = _idictentryarrayof(d, entry->key);
    
    /* deal with entry-array */
    if (indexentrys == NULL) {
        /* make indexentry array */
        indexentrys = _idictentryarraymake_forvalue(d, 8);
        iarrayset(d->values, _idictkeyindex(d, entry->key), &indexentrys);
        /* release the reference */
        irelease(indexentrys);
    }
    
    /*add to values */
    _idictentryadd(d, indexentrys, entry);
    /* collides with the keys */
    if (iarraylen(indexentrys) > 1) {
        d->priv->collides++;
    }
}

/* grow the capacity */
static void _idictgrowcapacity_rehashing(idict *d) {
    /*clear the collides */
    d->priv->collides = 0;
    /* make new one with new-capaicty */
    iarray *nvalues = iarraymakeiref(_idictnewcapacity(d));
    /* raw-set the size to new-capacity */
    nvalues->len = nvalues->capacity;
    /* attach the nvalues */
    iassign(d->values, nvalues);
    /* release the reference */
    irefdelete(nvalues);
    
    /* rehashing all the entrys */
    irangearray(d->keys, idictentry*,
                _idictrehashingentry(d, __value);
                );
}

/* shrink the capacity */
static void _idictshrinkcapacity_rehashing(idict *d) {
    /*clear the collides */
    d->priv->collides = 0;
    /* make new one with new-capaicty */
    iarray *nvalues = iarraymakeiref(_idictnewshrinkcapacity(d));
    /* raw-set the size to new-capacity */
    nvalues->len = nvalues->capacity;
    /* attach the nvalues */
    iassign(d->values, nvalues);
    /* release the reference */
    irefdelete(nvalues);
    
    /* rehashing all the entrys */
    irangearray(d->keys, idictentry*,
                _idictrehashingentry(d, __value);
                );
}

/* will auto-rehashing the dict by collides */
static void _idict_auto_rehashing(idict *d) {
    size_t nkeys = iarraylen(d->keys);
    size_t nvalues = iarraylen(d->values);
    size_t ncollides = d->priv->collides;
    if (nkeys > 3*nvalues ) {   /* there are 3 doubles of pair in buckect */
        _idictgrowcapacity_rehashing(d);
    } else if (nkeys > nvalues && ncollides > nkeys/3 ) {   /* the collides more than 1/2 keys */
        _idictgrowcapacity_rehashing(d);
    } else if (nkeys && nvalues > 10 * nkeys && ncollides <= nkeys/3 ) {
        _idictshrinkcapacity_rehashing(d);
    }
}

/* make a dicit with default-capacity */
idict *idictmake(size_t capacity) {
    return idictmakewith(capacity, 0);
}

/* make a dicit with default-capacity */
idict *idictmakewith(size_t capacity, int flag) {
    idict *d = irefnew(idict);
    d->keys = _idictentryarraymake_forkey(d, capacity); /*ivar array */
    d->values = iarraymakeiref(capacity);           /*iarray array */
    d->values->len = capacity; /* raw- empty- ref array with capacity */
    d->flag = flag;
    
    d->priv = (idict_private*)icalloc(1, sizeof(idict_private));
    return d;
}

/* the number of entry */
size_t idictsize(const idict *d) {
    return iarraylen(d->keys);
}

/* find the value for key, return iiok or iino */
int idicthas(const idict *d, const ivar *key) {
    iarray* indexentrys = _idictentryarrayof(d, key);
    return _idictentryindexof(d, indexentrys, key) != kindex_invalid;
}

/* find the value for key, return iiok or iino [retain-key] [retain-value] */
idictentry* idictadd(idict *d, const ivar *key, ivar *value) {
    iarray* indexentrys = _idictentryarrayof(d, key);
    idictentry *entry = NULL;
    
    /* auto-rehashing */
    if (iflag_is(d->flag, EnumDictFlag_AutoRehashing)) {
        _idict_auto_rehashing(d);
    }
    
    /* deal with entry-array */
    if (indexentrys == NULL) {
        /* make indexentry array */
        indexentrys = _idictentryarraymake_forvalue(d, 8);
        iarrayset(d->values, _idictkeyindex(d, key), &indexentrys);
        /* release the reference */
        irelease(indexentrys);
    } else {
        /* get the */
        entry = _idictentryof(d, indexentrys, key);
    }
    
    /* deal with entry */
    if (!entry) {
        entry = idictentrymake((ivar*)key);
        /*set value for key */
        idictentysetvalue(entry, value);
        /*add to values */
        _idictentryadd(d, indexentrys, entry);
        /*add keys */
        _idictentryadd(d, d->keys, entry);
        /* free the tmp entry but not clear, we will return it as holded by array */
        irelease(entry);
        
        /* collides with the keys */
        if (iarraylen(indexentrys) > 1) {
            d->priv->collides++;
        }
    } else {
        /* replace the entry with key */
        idictentysetvalue(entry, value);
    }
    
    return entry;
}

/* remove the value with key */
int idictremove(idict *d, const ivar *key) {
    iarray* indexentrys = _idictentryarrayof(d, key);
    idictentry *entry = NULL;
    if (indexentrys && iarraylen(indexentrys)) {
        entry = _idictentryof(d, indexentrys, key);
        return idictremoveentry(d, entry, indexentrys);
    }
    
    return iino;
}

/* remove the entry in dict */
int idictremoveentry(idict *d, idictentry *entry, iarray* indexentrys) {
    icheckret(d && entry, iino);
    
    if (indexentrys == NULL) {
        indexentrys = _idictentryarrayof(d, entry->key);
    }
    
    /* remove value */
    iarrayremove(indexentrys, entry->indexvalue);
    /* remove key */
    iarrayremove(d->keys, entry->indexkey);
    
    /* minus the collides */
    if (iarraylen(indexentrys) > 0) {
        d->priv->collides--;
    }
    
    /* auto-rehashing */
    if (iflag_is(d->flag, EnumDictFlag_AutoRehashing)) {
        _idict_auto_rehashing(d);
    }
    
    return iiok;
}

/* remove all the values in dict */
int idictremoveall(idict *d) {
    /* skip the empty array */
    icheckret(d && iarraylen(d->keys), iiok);
    
    /* remove all keys */
    iarrayremoveall(d->keys);
    
    /* remove all values */
    iarray* indexentrys = NULL;
    irangearray(d->values, iarray*,
                iarrayset(d->values, __key, &indexentrys);
                );
    
    /* auto-rehashing */
    if (iflag_is(d->flag, EnumDictFlag_AutoRehashing)) {
        _idict_auto_rehashing(d);
    }
    
    return iiok;
}

/* fech the value with key, if exits [no-retain-ret] */
ivar* idictvalue(const idict *d, const ivar *key) {
    idictentry *entry = idictentryof(d, key);
    if (entry) {
        return icast(ivar, entry->value);
    }
    return NULL;
}

/* fech the entry with key, if exits [no-retain-ret] */
idictentry* idictentryof(const idict *d, const ivar *key) {
    iarray* indexentrys = _idictentryarrayof(d, key);
    if (indexentrys && iarraylen(indexentrys)) {
        return _idictentryof(d, indexentrys, key);
    }
    return NULL;
}

/* get all sorted keys */
const iarray* idictkeys(const idict *d) {
    return d->keys;
}

/* the dict destructor */
void idict_destructor(const struct imeta *meta, iptr o) {
    idict *d = icast(idict, o);
    irefdelete(d->keys);
    irefdelete(d->values);
    
    ifree(d->priv);
    d->priv = NULL;
}
    
/* the dict hash */
uint64_t idict_hash(const struct imeta *meta, iconstptr o) {
    return 0;
}
 
