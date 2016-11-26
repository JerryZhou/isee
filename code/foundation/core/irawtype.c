#include "foundation/core/irawtype.h"
#include "foundation/core/imeta.h"
#include "foundation/math/imd5.h"
#include "foundation/memory/imemory.h"


/* inull: meta-hash */
uint64_t inull_hash(const struct imeta *meta, iconstptr o) {
    inull *n = icast(inull, o);
    return *n == iiok;
}
/* inull: meta-compare */
int inull_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    inull *l = icast(inull, lfs);
    inull *r = icast(inull, rfs);
    return *l == *r;
}
/* inull: meta-assign */
void inull_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    inull *d = icast(inull, dst);
    inull *s = icast(inull, src);
    *d = *s;
}

/* int: meta-hash */
uint64_t int_hash(const struct imeta *meta, iconstptr o) {
    int *n = icast(int, o);
    return *n;
}
/* int: meta-compare */
int int_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    int *l = icast(int, lfs);
    int *r = icast(int, rfs);
    return *l - *r;
}
/* int: meta-assign */
void int_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    int *d = icast(int, dst);
    int *s = icast(int, src);
    *d = *s;
}

/* int32_t: meta-hash */
uint64_t int32_t_hash(const struct imeta *meta, iconstptr o) {
    int32_t *n = icast(int32_t, o);
    return *n;
}
/* int32_t: meta-compare */
int int32_t_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    int32_t *l = icast(int32_t, lfs);
    int32_t *r = icast(int32_t, rfs);
    return *l - *r;
}
/* int32_t: meta-assign */
void int32_t_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    int32_t *d = icast(int32_t, dst);
    int32_t *s = icast(int32_t, src);
    *d = *s;
}

/* uint32_t: meta-hash */
uint64_t uint32_t_hash(const struct imeta *meta, iconstptr o) {
    uint32_t *n = icast(uint32_t, o);
    return *n;
}
/* uint32_t: meta-compare */
int uint32_t_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    uint32_t *l = icast(uint32_t, lfs);
    uint32_t *r = icast(uint32_t, rfs);
    return *l - *r;
}
/* uint32_t: meta-assign */
void uint32_t_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    uint32_t *d = icast(uint32_t, dst);
    uint32_t *s = icast(uint32_t, src);
    *d = *s;
}

/* int64_t: meta-hash */
uint64_t int64_t_hash(const struct imeta *meta, iconstptr o) {
    int64_t *n = icast(int64_t, o);
    return *n;
}
/* int64_t: meta-compare */
int int64_t_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    int64_t *l = icast(int64_t, lfs);
    int64_t *r = icast(int64_t, rfs);
    return *l - *r;
}
/* int64_t: meta-assign */
void int64_t_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    int64_t *d = icast(int64_t, dst);
    int64_t *s = icast(int64_t, src);
    *d = *s;
}

/* uint64_t: meta-hash */
uint64_t uint64_t_hash(const struct imeta *meta, iconstptr o) {
    uint64_t *n = icast(uint64_t, o);
    return *n;
}
/* uint64_t: meta-compare */
int uint64_t_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    uint64_t *l = icast(uint64_t, lfs);
    uint64_t *r = icast(uint64_t, rfs);
    return *l - *r;
}
/* uint64_t: meta-assign */
void uint64_t_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    uint64_t *l = icast(uint64_t, dst);
    uint64_t *r = icast(uint64_t, src);
    *l = *r;
}

/* ireal: meta-hash */
uint64_t ireal_hash(const struct imeta *meta, iconstptr o) {
    uint64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* ireal: meta-compare */
int ireal_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    ireal *l = icast(ireal, lfs);
    ireal *r = icast(ireal, rfs);
    return *l - *r;
}
/* ireal: meta-assign */
void ireal_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    ireal *l = icast(ireal, dst);
    ireal *r = icast(ireal, src);
    *l = *r;
}

/* float: meta-hash */
uint64_t float_hash(const struct imeta *meta, iconstptr o) {
    uint64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* float: meta-compare */
int float_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    float *l = icast(float, lfs);
    float *r = icast(float, rfs);
    return *l - *r;
}
/* float: meta-assign */
void float_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    float *l = icast(float, dst);
    float *r = icast(float, src);
    *l = *r;
}

/* double: meta-hash */
uint64_t double_hash(const struct imeta *meta, iconstptr o) {
    uint64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* double: meta-compare */
int double_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    double *l = icast(double, lfs);
    double *r = icast(double, rfs);
    return *l - *r;
}
/* double: meta-assign */
void double_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    double *l = icast(double, dst);
    double *r = icast(double, src);
    *l = *r;
}

/* ibyte: meta-hash */
uint64_t ibyte_hash(const struct imeta *meta, iconstptr o) {
    uint64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* ibyte: meta-compare */
int ibyte_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    ibyte *l = icast(ibyte, lfs);
    ibyte *r = icast(ibyte, rfs);
    return *l - *r;
}
/* ibyte: meta-assign */
void ibyte_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    ibyte *l = icast(ibyte, dst);
    ibyte *r = icast(ibyte, src);
    *l = *r;
}

/* ibool: meta-hash */
uint64_t ibool_hash(const struct imeta *meta, iconstptr o) {
    uint64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* ibool: meta-compare */
int ibool_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    ibool *l = icast(ibool, lfs);
    ibool *r = icast(ibool, rfs);
    return *l == *r;
}
/* ibool: meta-assign */
void ibool_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    ibool *l = icast(ibool, dst);
    ibool *r = icast(ibool, src);
    *l = *r;
}

/* iptr: meta-hash */
uint64_t iptr_hash(const struct imeta *meta, iconstptr o) {
    uint64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* iptr: meta-compare */
int iptr_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    iptr *l = icast(iptr, lfs);
    iptr *r = icast(iptr, rfs);
    return l - r;
}
/* iptr: meta-assign */
void iptr_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    iptr *l = icast(iptr, dst);
    iptr *r = icast(iptr, src);
    *l = *r;
}

/* pod destructor */
void ipod_destructor(const struct imeta *meta, iptr o) {
    ipod *p = icast(ipod, o);
    if (p->ptr && p->ptr != p->stbuf) {
        ifree(p->ptr);
        p->ptr = p->stbuf;
    }
}
/* ipod: meta-hash */
uint64_t ipod_hash(const struct imeta *meta, iconstptr o) {
    ipod *pod = icast(ipod, o);
    imd5 md5;
    imd5reset(&md5);
    imd5write(&md5, (unsigned char*)pod->ptr, pod->size);
    return imd5sum(&md5);
}
/* ipod: meta-compare */
int ipod_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    ipod *l = icast(ipod, lfs);
    ipod *r = icast(ipod, rfs);
    if (l->size != r->size) {
        return l->size - r->size;
    }
    return memcmp(l->ptr, r->ptr, imin(l->size, r->size));
}
/* ipod: meta-assign */
void ipod_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    ipod *l = icast(ipod, dst);
    ipod *r = icast(ipod, src);
    ipod_destructor(meta, dst);
    ipod_init(l, r->ptr, r->size, r->align);
}

/* ipod: init */
void ipod_init(ipod *p, const void* byte, size_t size, size_t align) {
    p->align = align;
    p->size = size;
    p->ptr = p->stbuf;
    if (size > sizeof(p->stbuf)) {
        p->ptr = icalloc(1, size);
    }
    memcpy(p->ptr, byte, size);
}

/* irune: meta-hash */
uint64_t irune_hash(const struct imeta *meta, iconstptr o) {
    uint64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* irune: meta-compare */
int irune_compare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    irune *l = icast(irune, lfs);
    irune *r = icast(irune, rfs);
    return *l - *r;
}
/* irune: meta-assign */
void irune_assign(const struct imeta *meta, iptr dst, iconstptr src) {
    irune *l = icast(irune, dst);
    irune *r = icast(irune, src);
    *l = *r;
}

