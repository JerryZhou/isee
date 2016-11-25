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
#define irealimplementregisterfull(type, xsize, xalign, xflag, \
        xcapacity, xmptr, xconstructor, xdestructor, xhash, xcompare, xassign) \
    config.name = #type; config.size=xsize; config.align = xalign; config.flag = xflag;\
    config.capacity=xcapacity; \
    config.constructor = xconstructor; config.destructor=xdestructor;\
    config.hash = xhash; config.compare = xcompare; config.assign = xassign;\
    imetaindex(type) = imetaregisterwithconfig(&config)
/* meta-index registing in runtime */
#define iimplementregister(type, capacity) int irealimplementregister(type, capacity)

/* declare all the types for user defines */
#define __iudeclaremeta(type, xsize, xalign, xflag, xcapacity,  xmptr, xconstructor, xdestructor, xhash, xcompare, xcopy) iideclareregister(type)

/* declare all the foundation types meta */
#define __ideclaremeta(type, xsize, xalign, xflag, xcapacity,  xmptr, xconstructor, xdestructor, xhash, xcompare, xassign) imetaindex(type)

#define __iallmeta    \
__ideclaremeta(inull,    sizeof(inull),    sizeof(inull),   EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(int,      sizeof(int),      sizeof(int),     EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(int32_t,  sizeof(int32_t),  sizeof(int32_t), EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(uint32_t, sizeof(uint32_t), sizeof(uint32_t),EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(int64_t,  sizeof(int64_t),  sizeof(int64_t), EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(uint64_t, sizeof(uint64_t), sizeof(uint64_t),EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(ireal,    sizeof(ireal),    sizeof(ireal),   EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(float,    sizeof(float),    sizeof(float),   EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(double,   sizeof(double),   sizeof(double),  EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(ibyte,    sizeof(ibyte),    sizeof(ibyte),   EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(ibool,    sizeof(ibool),    sizeof(ibool),   EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(iptr,     sizeof(iptr),     sizeof(iptr),    EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(ipod,     sizeof(ipod),     0,               EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(irune,    sizeof(irune),    sizeof(irune),   EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(imd5,     sizeof(imd5),     0,               EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(iobj,     sizeof(iobj),     0,               EnumMetaFlag_POD,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(iobjcache,sizeof(iobjcache),0,               EnumMetaFlag_Ref,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(iref,     sizeof(iref),     0,               EnumMetaFlag_Ref,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(iwref,    sizeof(iwref),    0,               EnumMetaFlag_Ref,0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(ivar,     sizeof(ivar),     0,               EnumMetaFlag_Ref,0, NULL, NULL, ivar_destructor, ivar_hash, ivar_compare, ivar_assign),\
__ideclaremeta(irefcache,sizeof(irefcache),0,               EnumMetaFlag_Ref,0, NULL, NULL, irefcache_destructor, NULL, NULL, NULL),\
__ideclaremeta(irefjoint,sizeof(irefjoint),0,               EnumMetaFlag_Ref,0, NULL, NULL, irefjoint_destructor, NULL, NULL, NULL),\
__ideclaremeta(ireflist, sizeof(ireflist),0,                EnumMetaFlag_Ref,0, NULL, NULL, ireflist_destructor, NULL, NULL, NULL),\
__ideclaremeta(iarray,   sizeof(iarray),0,            EnumMetaFlag_Ref,  10000, NULL, NULL, iarray_destructor, NULL, NULL, NULL),\
__ideclaremeta(iarrayentry,sizeof(iarrayentry),           0,EnumMetaFlag_POD,1000, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(irefarrayentry,sizeof(irefarrayentry),     0,EnumMetaFlag_POD,1000, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(islice, sizeof(islice),0, EnumMetaFlag_Ref, 10000, NULL, NULL, islice_destructor, NULL, NULL, NULL),\
__ideclaremeta(istring,sizeof(istring),0,EnumMetaFlag_Ref,10000, NULL, NULL, islice_destructor, istring_hash, istring_compare, NULL),\
__ideclaremeta(icmdarg,  sizeof(icmdarg),    0,  EnumMetaFlag_Ref,   0, NULL, NULL, icmdarg_destructor, NULL, NULL, NULL),\
__ideclaremeta(itree,    sizeof(itree),0,        EnumMetaFlag_Ref,   0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(idict,   sizeof(idict),0,         EnumMetaFlag_Ref,   0, NULL, NULL, NULL, NULL, NULL, NULL),\
__ideclaremeta(ineighbor,sizeof(ineighbor),    0,EnumMetaFlag_Ref,   0, NULL, NULL, ineighbor_destructor, NULL, NULL, NULL),\
__ideclaremeta(iringbuffer,sizeof(iringbuffer),0,EnumMetaFlag_Ref,   0, NULL, NULL, iringbuffer_destructor, NULL, NULL, NULL),\
__ideclaremeta(ipolygon3d, sizeof(ipolygon3d), 0,EnumMetaFlag_Ref, 1000, NULL, NULL, ipolygon3d_destructor, NULL, NULL, NULL),\
__ideclaremeta(ipolygon2d, sizeof(ipolygon2d), 0,EnumMetaFlag_Ref, 1000, NULL, NULL, ipolygon2d_destructor, NULL, NULL, NULL),\
__ideclaremeta(imeta,      sizeof(imeta),      0,EnumMetaFlag_Complex,0, NULL, NULL, NULL, NULL, NULL, NULL)


/* all meta-indexs */
typedef enum EnumMetaTypeIndex {
    __iallmeta,
    EnumMetaTypeIndex_imax,
} EnumMetaTypeIndex;

/* support IMaxMetaCountForUser user define meta-type */
#define IMaxMetaCountForUser 512
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
