#ifndef _IMETATYPES_H_
#define _IMETATYPES_H_

#include "foundation/imeta.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* meta-index */
#define imetaindex(type) imeta_##type##_index
/* meta-registing with cache */
#define iregister(type, capacity) imetaregister(#type, sizeof(type), capacity)
/* meta-index declare */
#define irealdeclareregister(type) int imetaindex(type)
/* meta-index extern declare */
#define iideclareregister(type) extern irealdeclareregister(type)
/* meta-index registing */
#define irealimplementregister(type, capacity) imetaindex(type) = iregister(type, capacity)
/* meta-index registing in runtime */
#define iimplementregister(type, capacity) int irealimplementregister(type, capacity)
/* meta-get by meta-index */
#define imetaof(type) imetaget(imetaindex(type))

/* declare all the foundation types meta */
#define __ideclaremeta(type, capacity) imetaindex(type)

#define __iallmeta                            \
__ideclaremeta(iobj, 0)

/* all meta-indexs */
typedef enum EnumMetaTypeIndex {
    __iallmeta,
    EnumMetaTypeIndex_imax,
}EnumMetaTypeIndex;

/* support IMaxMetaCountForUser user define meta-type */
#define IMaxMetaCountForUser 512
    
/* include imetatypes.h */
#define iobjmalloc(type) ((type*)imetacalloc(imetaof(type)))
#define iobjfree(p) do { imetafree(p); p = NULL; } while(0)
/* quickly type-compare */
#define iistype(p, type) (iobjgetmeta(p) == imetaof(type))
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif