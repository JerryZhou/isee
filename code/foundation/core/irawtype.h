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
uint64_t inull_hash(const struct imeta *meta, iconstptr o);
/* inull: meta-compare */
int inull_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* inull: meta-assign */
void inull_assign(const struct imeta *meta, iptr dst, iconstptr src);
    
/* int: meta-hash */
uint64_t int_hash(const struct imeta *meta, iconstptr o);
/* int: meta-compare */
int int_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* int: meta-assign */
void int_assign(const struct imeta *meta, iptr dst, iconstptr src);
    
/* int32_t: meta-hash */
uint64_t int32_t_hash(const struct imeta *meta, iconstptr o);
/* int32_t: meta-compare */
int int32_t_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* int32_t: meta-assign */
void int32_t_assign(const struct imeta *meta, iptr dst, iconstptr src);
    
/* uint32_t: meta-hash */
uint64_t uint32_t_hash(const struct imeta *meta, iconstptr o);
/* uint32_t: meta-compare */
int uint32_t_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* uint32_t: meta-assign */
void uint32_t_assign(const struct imeta *meta, iptr dst, iconstptr src);
    
/* int32_t: meta-hash */
uint64_t int64_t_hash(const struct imeta *meta, iconstptr o);
/* int32_t: meta-compare */
int int64_t_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* int32_t: meta-assign */
void int64_t_assign(const struct imeta *meta, iptr dst, iconstptr src);
    
/* uint64_t: meta-hash */
uint64_t uint64_t_hash(const struct imeta *meta, iconstptr o);
/* uint64_t: meta-compare */
int uint64_t_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* uint64_t: meta-assign */
void uint64_t_assign(const struct imeta *meta, iptr dst, iconstptr src);
    
/* ireal: meta-hash */
uint64_t ireal_hash(const struct imeta *meta, iconstptr o);
/* ireal: meta-compare */
int ireal_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* ireal: meta-assign */
void ireal_assign(const struct imeta *meta, iptr dst, iconstptr src);

/* float: meta-hash */
uint64_t float_hash(const struct imeta *meta, iconstptr o);
/* float: meta-compare */
int float_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* float: meta-assign */
void float_assign(const struct imeta *meta, iptr dst, iconstptr src);

/* double: meta-hash */
uint64_t double_hash(const struct imeta *meta, iconstptr o);
/* double: meta-compare */
int double_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* double: meta-assign */
void double_assign(const struct imeta *meta, iptr dst, iconstptr src);

/* ibyte: meta-hash */
uint64_t ibyte_hash(const struct imeta *meta, iconstptr o);
/* ibyte: meta-compare */
int ibyte_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* ibyte: meta-assign */
void ibyte_assign(const struct imeta *meta, iptr dst, iconstptr src);

/* ibool: meta-hash */
uint64_t ibool_hash(const struct imeta *meta, iconstptr o);
/* ibool: meta-compare */
int ibool_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* ibool: meta-assign */
void ibool_assign(const struct imeta *meta, iptr dst, iconstptr src);

/* iptr: meta-hash */
uint64_t iptr_hash(const struct imeta *meta, iconstptr o);
/* iptr: meta-compare */
int iptr_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* iptr: meta-assign */
void iptr_assign(const struct imeta *meta, iptr dst, iconstptr src);
    
/* pod destructor */
void ipod_destructor(const struct imeta *meta, iptr o);
/* ipod: meta-hash */
uint64_t ipod_hash(const struct imeta *meta, iconstptr o);
/* ipod: meta-compare */
int ipod_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* ipod: meta-assign */
void ipod_assign(const struct imeta *meta, iptr dst, iconstptr src);
    
/* irune: meta-hash */
uint64_t irune_hash(const struct imeta *meta, iconstptr o);
/* irune: meta-compare */
int irune_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
/* irune: meta-assign */
void irune_assign(const struct imeta *meta, iptr dst, iconstptr src);


/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IRAWTYPE_H_ */
