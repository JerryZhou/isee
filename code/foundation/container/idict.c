#include "foundation/container/idict.h"
#include "foundation/util/iarraytypes.h"
#include "foundation/memory/imemory.h"


/* make a entry with key */
idictentry* idictentrymake(ivar *key) {
    idictentry *entry = irefnew(idictentry);
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

/*************************************************************/
/* iarray - idictentry                                             */
/*************************************************************/

/* array-idictentry assign */
static void _iarray_entry_assign_idictentry(struct iarray *arr,
                                      int i, const void *value, int nums) {
    idictentry *arrs = (idictentry *)arr->buffer;
    idictentry *dvalues = (idictentry *)value;
    int j = 0;
    
    /* for nums */
    while (j < nums) {
        /* realloc not set zero to pending memory */
        if (i >= arr->len) {
            arrs[i].key = NULL;
            arrs[i].value = NULL;
        }
        
        idictentry_assign(imetaof(idictentry), arrs + i, dvalues + j);
        
        ++j;
        ++i;
    }
}

/* swap the idictentry */
static void _iarray_entry_swap_idictentry(struct iarray *arr,
                                    int i, int j) {
    idictentry tmp = {.key = NULL, .value=NULL};
    idictentry *arrs = (idictentry *)arr->buffer;
    
    if (j == kindex_invalid) {
        /* arr_int[i] = 0;
         * may call assign */
        idictentry_assign(imetaof(idictentry), arrs+i, &tmp);
    } else if (i == kindex_invalid) {
        /* arr_int[j] = 0;
         * may call assign */
        idictentry_assign(imetaof(idictentry), arrs+j, &tmp);
    } else {
        tmp = arrs[i];
        arrs[i] = arrs[j];
        arrs[j] = tmp;
    }
}

/* compare idictentry */
static int _iarray_entry_cmp_idictentry(struct iarray *arr,
                                  int i, int j) {
    idictentry *arrs = (idictentry *)arr->buffer;
    /* the meta compare-funcs */
    const imeta *meta = imetaof(idictentry);
    return idictentry_compare(meta, arrs +i, arrs + j);
}

/* idictentry array-entry */
static iarrayentry _idictentry_arrayentry = {
    .flag = 0,
    .size = sizeof(idictentry),
    .cmp = _iarray_entry_cmp_idictentry,
    .swap = _iarray_entry_swap_idictentry,
    .assign = _iarray_entry_assign_idictentry
};

/* make a capacity of idictentry array */
iarray *_idictentyarraymake(size_t capacity) {
    return iarraymake(capacity, &_idictentry_arrayentry);
}

/* find in idictentry-array for key */
int _idictentryindexof(iarray *arr, const ivar *key) {
    icheckret(arr, kindex_invalid);
    icheckret(key, kindex_invalid);
    irangearray(arr, idictentry,
                if (ivarcompare(__value.key, key) == 0) {
                    return __key;
                }
                );
    return kindex_invalid;
}

/* remove the right-key in idictentry-array */
int _dictentryremove(iarray *arr, const ivar *key) {
    irangearray(arr, idictentry,
                if (ivarcompare(__value.key, key) == 0) {
                    iarrayremove(arr, __key);
                    return __key;
                }
                );
    return kindex_invalid;
}

/* get the idictentry of value in arr */
idictentry* _idictentryof(iarray *arr, const ivar *key) {
    irangearray(arr, idictentry,
                if (ivarcompare(__value.key, key)) {
                    return &iarrayof(arr, idictentry, __key);
                }
                );
    return NULL;
}

/* make a dicit with default-capacity */
idict *idictmake(int capacity) {
    idict *d = irefnew(idict);
    d->keys = _idictentyarraymake(capacity); /*ivar array */
    d->values = iarraymakeiref(capacity); /*iarray array */
    d->values->len = capacity; /* raw- empty- ref array with capacity */
    
    d->priv = (idict_private*)icalloc(1, sizeof(idict_private));
    return d;
}

/* the number of entry */
size_t idictsize(const idict *d) {
    return iheapsize(d->keys);
}

size_t _idictcapacity(const idict *d) {
    return iarraycapacity(d->values);
}

size_t _idictnewcapacity(const idict *d) {
    return _idictcapacity(d) * 2;
}

void _idictgrowcapacity(idict *d) {
    /* make new one with new-capaicty */
    iarray *nvalues = iarraymakeiref(_idictnewcapacity(d));
    /* copy old data from the old arrays */
    iarrayappend(nvalues, iarraybuffer(d->values), _idictcapacity(d));
    /* raw-set the size to new-capacity */
    nvalues->len = nvalues->capacity;
    /* attach the nvalues */
    iassign(d->values, nvalues);
    /* release the reference */
    irefdelete(nvalues);
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

/* find the value for key, return iiok or iino */
int idicthas(const idict *d, const ivar *key) {
    iarray* indexentrys = _idictentryarrayof(d, key);
    return _idictentryindexof(indexentrys, key) != kindex_invalid;
}

/* find the value for key, return iiok or iino [retain-key] [retain-value] */
int idictadd(idict *d, const ivar *key, ivar *value) {
    iarray* indexentrys = _idictentryarrayof(d, key);
    idictentry *entry = NULL;
    
    if (indexentrys == NULL) {
        indexentrys = _idictentyarraymake(8);
        iarrayset(d->values, _idictkeyindex(d, key), &indexentrys);
    } else {
        entry = _idictentryof(indexentrys, key);
    }
    if (!entry) {
        entry = idictentrymake((ivar*)key);
        /*add to values */
        iarrayadd(indexentrys, entry);
        /*add keys */
        iarrayadd(d->keys, entry);
    }
    idictentysetvalue(entry, value);
    return iiok;
}

/* remove the value with key */
int idictremove(idict *d, const ivar *key) {
    iarray* indexentrys = _idictentryarrayof(d, key);
    if (indexentrys && iarraylen(indexentrys)) {
        irangearray(indexentrys, idictentry,
                    if (ivarcompare(__value.key, key) == 0) {
                        /* remove value */
                        iarrayremove(indexentrys, __key);
                        /* remove key */
                        _dictentryremove(d->keys, __key);
                        return iiok;
                    }
                    );
    }
    return iino;
}

/* fech the value with key, if exits [no-retain-ret] */
ivar* idictvalue(const idict *d, const ivar *key) {
    iarray* indexentrys = _idictentryarrayof(d, key);
    if (indexentrys && iarraylen(indexentrys)) {
        irangearray(indexentrys, idictentry,
                    if (ivarcompare(__value.key, key) == 0) {
                        return __value.value;
                    }
                    );
    }
    return NULL;
}

/* get all sorted keys */
const iarray* idicttkeys(const idict *d) {
    return d->keys;
}

/* the dict destructor */
void idict_destructor(const struct imeta *meta, iptr o) {
    idict *d = icast(idict, o);
    irefdelete(d->keys);
    irefdelete(d->values);
}
    
/* the dict hash */
void idict_hash(const struct imeta *meta, iconstptr o);
 
