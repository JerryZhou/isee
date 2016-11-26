#ifndef _IDICT_H_
#define _IDICT_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iref.h"

#include "foundation/core/ivar.h"
#include "foundation/container/iheap.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* the inner struct declares */
struct idict_private;
   
/* the idict entry */
typedef struct idictentry {
    ivar *key;
    ivar *value;
} idictentry;

/* make a entry with key */
idictentry* idictentrymake(ivar *key);

/* get a key from entry */
ivar *idictentrykey(const idictentry *e);

/* get a value from entry */
ivar *idictentryvalue(const idictentry *e);

/* set a value for entry */
void idictentysetvalue(idictentry *e, ivar *value);

/* release all the resources with entry */
void idictentry_destructor(const struct imeta *meta, iptr o);

/* the same as hash on key */
uint64_t idictentry_hash(const struct imeta *meta, iconstptr o);

/* the meta assign */
void idictentry_assign(const struct imeta *meta, iptr dst, iconstptr src);

/* the same as compare on key */
int idictentry_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);

/* the ivar hash-map */
typedef struct idict {
    irefdeclare;
    
    iheap* keys;      /* heap<ivar> */
    iarray* values;   /* array<iarray> */
    
    struct idict_private *priv;
} idict;

/* make a dicit with default-capacity */
idict *idictmake(int capacity);
    
/* the number of entry */
size_t idictsize(const idict *d);

/* find the value for key, return iiok or iino */
int idicthas(const idict *d, const ivar *key);

/* find the value for key, return iiok or iino [retain-key] [retain-value] */
int idictadd(idict *d, const ivar *key, ivar *value);

/* remove the value with key */
int idictremove(idict *d, const ivar *key);

/* fech the value with key, if exits [no-retain-ret] */
ivar* idictvalue(const idict *d, const ivar *key);

/* get all sorted keys */
const iarray* idicttkeys(const idict *d);
    
/* the dict destructor */
void idict_destructor(const struct imeta *meta, iptr o);
    
/* the dict hash */
void idict_hash(const struct imeta *meta, iconstptr o);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IDICT_H_ */
