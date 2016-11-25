#ifndef _IRAWTYPE_H_
#define _IRAWTYPE_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* forward declares */
struct imeta;
    
/* inull: meta-hash */
int64_t inull_hash(const struct imeta *meta, const iptr o);
/* inull: meta-compare */
int inull_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* inull: meta-assign */
void inull_assign(const struct imeta *meta, iptr dst, const iptr src);
    
/* int: meta-hash */
int64_t int_hash(const struct imeta *meta, const iptr o);
/* int: meta-compare */
int int_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* int: meta-assign */
void int_assign(const struct imeta *meta, iptr dst, const iptr src);
    
/* int32_t: meta-hash */
int64_t int32_t_hash(const struct imeta *meta, const iptr o);
/* int32_t: meta-compare */
int int32_t_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* int32_t: meta-assign */
void int32_t_assign(const struct imeta *meta, iptr dst, const iptr src);
    
/* uint32_t: meta-hash */
int64_t uint32_t_hash(const struct imeta *meta, const iptr o);
/* uint32_t: meta-compare */
int uint32_t_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* uint32_t: meta-assign */
void uint32_t_assign(const struct imeta *meta, iptr dst, const iptr src);
    
/* int32_t: meta-hash */
int64_t int64_t_hash(const struct imeta *meta, const iptr o);
/* int32_t: meta-compare */
int int64_t_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* int32_t: meta-assign */
void int64_t_assign(const struct imeta *meta, iptr dst, const iptr src);
    
/* uint64_t: meta-hash */
int64_t uint64_t_hash(const struct imeta *meta, const iptr o);
/* uint64_t: meta-compare */
int uint64_t_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* uint64_t: meta-assign */
void uint64_t_assign(const struct imeta *meta, iptr dst, const iptr src);
    
/* ireal: meta-hash */
int64_t ireal_hash(const struct imeta *meta, const iptr o);
/* ireal: meta-compare */
int ireal_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* ireal: meta-assign */
void ireal_assign(const struct imeta *meta, iptr dst, const iptr src);

/* float: meta-hash */
int64_t float_hash(const struct imeta *meta, const iptr o);
/* float: meta-compare */
int float_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* float: meta-assign */
void float_assign(const struct imeta *meta, iptr dst, const iptr src);

/* double: meta-hash */
int64_t double_hash(const struct imeta *meta, const iptr o);
/* double: meta-compare */
int double_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* double: meta-assign */
void double_assign(const struct imeta *meta, iptr dst, const iptr src);

/* ibyte: meta-hash */
int64_t ibyte_hash(const struct imeta *meta, const iptr o);
/* ibyte: meta-compare */
int ibyte_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* ibyte: meta-assign */
void ibyte_assign(const struct imeta *meta, iptr dst, const iptr src);

/* ibool: meta-hash */
int64_t ibool_hash(const struct imeta *meta, const iptr o);
/* ibool: meta-compare */
int ibool_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* ibool: meta-assign */
void ibool_assign(const struct imeta *meta, iptr dst, const iptr src);

/* iptr: meta-hash */
int64_t iptr_hash(const struct imeta *meta, const iptr o);
/* iptr: meta-compare */
int iptr_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* iptr: meta-assign */
void iptr_assign(const struct imeta *meta, iptr dst, const iptr src);
    
/* pod destructor */
void ipod_destructor(const struct imeta *meta, iptr o);
/* ipod: meta-hash */
int64_t ipod_hash(const struct imeta *meta, const iptr o);
/* ipod: meta-compare */
int ipod_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* ipod: meta-assign */
void ipod_assign(const struct imeta *meta, iptr dst, const iptr src);
    
/* irune: meta-hash */
int64_t irune_hash(const struct imeta *meta, const iptr o);
/* irune: meta-compare */
int irune_compare(const struct imeta *meta, const iptr lfs, const iptr rfs);
/* irune: meta-assign */
void irune_assign(const struct imeta *meta, iptr dst, const iptr src);


/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IRAWTYPE_H_ */
