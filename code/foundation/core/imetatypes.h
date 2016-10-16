#ifndef _IMETATYPES_H_
#define _IMETATYPES_H_

#include "foundation/core/iobj.h"
#include "foundation/core/imeta.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* meta-registing with cache */
#define iregister(type, capacity) imetaregisterwithcapacity(#type, sizeof(type), capacity)
/* meta-index declare */
#define irealdeclareregister(type) int imetaindex(type)
/* meta-index extern declare */
#define iideclareregister(type) extern irealdeclareregister(type)
/* meta-index registing */
#define irealimplementregister(type, capacity) imetaindex(type) = iregister(type, capacity)
#define irealimplementregisterfull(type, xcapacity, xconstructor, xdestructor, xhash, xcompare) \
    config.name = #type; config.size=sizeof(type); config.capacity=xcapacity; \
    config.constructor = xconstructor; config.destructor=xdestructor;\
    config.hash = xhash; config.compare = xcompare;\
    imetaindex(type) = imetaregisterwithconfig(&config)
/* meta-index registing in runtime */
#define iimplementregister(type, capacity) int irealimplementregister(type, capacity)

/* declare all the types for user defines */
#define __iudeclaremeta(type) iideclareregister(type)
#define __iudeclaremetacapacity(type, capacity) iideclareregister(type)
#define __iudeclaremetapart(type, capacity, constructor, destructor) iideclareregister(type)
#define __iudeclaremetafull(type, capacity, constructor, destructor, hash, compare) iideclareregister(type)

/* declare all the foundation types meta */
#define __ideclaremeta(type) imetaindex(type)
#define __ideclaremetacapacity(type, capacity) imetaindex(type)
#define __ideclaremetapart(type, capacity, constructor, destructor) imetaindex(type)
#define __ideclaremetafull(type, capacity, constructor, destructor, hash, compare) imetaindex(type)

#define __iallmeta                            \
__ideclaremeta(iobj),\
__ideclaremeta(iobjcache),\
__ideclaremeta(iref),\
__ideclaremeta(iwref),\
__ideclaremetapart(irefcache, 0, NULL, irefcache_destructor),\
__ideclaremetapart(irefjoint, 0, NULL, irefjoint_destructor),\
__ideclaremetapart(ireflist, 0, NULL, ireflist_destructor),\
__ideclaremetapart(iarray, 1000, NULL, iarray_destructor),\
__ideclaremetacapacity(iarrayentry, 1000),\
__ideclaremetacapacity(irefarrayentry, 1000),\
__ideclaremetapart(islice, 1000, NULL, islice_destructor),\
__ideclaremetapart(icmdarg, 0, NULL, icmdarg_destructor),\
__ideclaremeta(itree),\
__ideclaremeta(idict),\
__ideclaremeta(ineighbor),\
__ideclaremetapart(iringbuffer, 0, NULL, iringbuffer_destructor),\
__ideclaremetapart(ipolygon3d, 1000, NULL, ipolygon3d_destructor),\
__ideclaremetapart(ipolygon2d, 1000, NULL, ipolygon2d_destructor),\
__ideclaremeta(imeta)


/* all meta-indexs */
typedef enum EnumMetaTypeIndex {
    __iallmeta,
    EnumMetaTypeIndex_imax,
}EnumMetaTypeIndex;

/* support IMaxMetaCountForUser user define meta-type */
#define IMaxMetaCountForUser 512
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif