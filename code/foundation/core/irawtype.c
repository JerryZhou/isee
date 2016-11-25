#include "foundation/core/irawtype.h"
#include "foundation/core/imeta.h"
#include "foundation/math/imd5.h"
#include "foundation/memory/imemory.h"


/* inull: meta-hash */
int64_t inull_hash(const struct imeta *meta, const iptr o) {
    inull *n = icast(inull, o);
    return *n == iiok;
}
/* inull: meta-compare */
int inull_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    inull *l = icast(inull, lfs);
    inull *r = icast(inull, rfs);
    return *l == *r;
}
/* inull: meta-assign */
void inull_assign(const struct imeta *meta, iptr dst, const iptr src) {
    inull *d = icast(inull, dst);
    inull *s = icast(inull, src);
    *d = *s;
}

/* int: meta-hash */
int64_t int_hash(const struct imeta *meta, const iptr o) {
    int *n = icast(int, o);
    return *n;
}
/* int: meta-compare */
int int_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    int *l = icast(int, lfs);
    int *r = icast(int, rfs);
    return *l - *r;
}
/* int: meta-assign */
void int_assign(const struct imeta *meta, iptr dst, const iptr src) {
    int *d = icast(int, dst);
    int *s = icast(int, src);
    *d = *s;
}

/* int32_t: meta-hash */
int64_t int32_t_hash(const struct imeta *meta, const iptr o) {
    int32_t *n = icast(int32_t, o);
    return *n;
}
/* int32_t: meta-compare */
int int32_t_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    int32_t *l = icast(int32_t, lfs);
    int32_t *r = icast(int32_t, rfs);
    return *l - *r;
}
/* int32_t: meta-assign */
void int32_t_assign(const struct imeta *meta, iptr dst, const iptr src) {
    int32_t *d = icast(int32_t, dst);
    int32_t *s = icast(int32_t, src);
    *d = *s;
}

/* uint32_t: meta-hash */
int64_t uint32_t_hash(const struct imeta *meta, const iptr o) {
    uint32_t *n = icast(uint32_t, o);
    return *n;
}
/* uint32_t: meta-compare */
int uint32_t_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    uint32_t *l = icast(uint32_t, lfs);
    uint32_t *r = icast(uint32_t, rfs);
    return *l - *r;
}
/* uint32_t: meta-assign */
void uint32_t_assign(const struct imeta *meta, iptr dst, const iptr src) {
    uint32_t *d = icast(uint32_t, dst);
    uint32_t *s = icast(uint32_t, src);
    *d = *s;
}

/* int64_t: meta-hash */
int64_t int64_t_hash(const struct imeta *meta, const iptr o) {
    int64_t *n = icast(int64_t, o);
    return *n;
}
/* int64_t: meta-compare */
int int64_t_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    int64_t *l = icast(int64_t, lfs);
    int64_t *r = icast(int64_t, rfs);
    return *l - *r;
}
/* int64_t: meta-assign */
void int64_t_assign(const struct imeta *meta, iptr dst, const iptr src) {
    int64_t *d = icast(int64_t, dst);
    int64_t *s = icast(int64_t, src);
    *d = *s;
}

/* uint64_t: meta-hash */
int64_t uint64_t_hash(const struct imeta *meta, const iptr o) {
    uint64_t *n = icast(uint64_t, o);
    return *n;
}
/* uint64_t: meta-compare */
int uint64_t_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    uint64_t *l = icast(uint64_t, lfs);
    uint64_t *r = icast(uint64_t, rfs);
    return *l - *r;
}
/* uint64_t: meta-assign */
void uint64_t_assign(const struct imeta *meta, iptr dst, const iptr src) {
    uint64_t *l = icast(uint64_t, dst);
    uint64_t *r = icast(uint64_t, src);
    *l = *r;
}

/* ireal: meta-hash */
int64_t ireal_hash(const struct imeta *meta, const iptr o) {
    int64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* ireal: meta-compare */
int ireal_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    ireal *l = icast(ireal, lfs);
    ireal *r = icast(ireal, rfs);
    return *l - *r;
}
/* ireal: meta-assign */
void ireal_assign(const struct imeta *meta, iptr dst, const iptr src) {
    ireal *l = icast(ireal, dst);
    ireal *r = icast(ireal, src);
    *l = *r;
}

/* float: meta-hash */
int64_t float_hash(const struct imeta *meta, const iptr o) {
    int64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* float: meta-compare */
int float_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    float *l = icast(float, lfs);
    float *r = icast(float, rfs);
    return *l - *r;
}
/* float: meta-assign */
void float_assign(const struct imeta *meta, iptr dst, const iptr src) {
    float *l = icast(float, dst);
    float *r = icast(float, src);
    *l = *r;
}

/* double: meta-hash */
int64_t double_hash(const struct imeta *meta, const iptr o) {
    int64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* double: meta-compare */
int double_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    double *l = icast(double, lfs);
    double *r = icast(double, rfs);
    return *l - *r;
}
/* double: meta-assign */
void double_assign(const struct imeta *meta, iptr dst, const iptr src) {
    double *l = icast(double, dst);
    double *r = icast(double, src);
    *l = *r;
}

/* ibyte: meta-hash */
int64_t ibyte_hash(const struct imeta *meta, const iptr o) {
    int64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* ibyte: meta-compare */
int ibyte_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    ibyte *l = icast(ibyte, lfs);
    ibyte *r = icast(ibyte, rfs);
    return *l - *r;
}
/* ibyte: meta-assign */
void ibyte_assign(const struct imeta *meta, iptr dst, const iptr src) {
    ibyte *l = icast(ibyte, dst);
    ibyte *r = icast(ibyte, src);
    *l = *r;
}

/* ibool: meta-hash */
int64_t ibool_hash(const struct imeta *meta, const iptr o) {
    int64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* ibool: meta-compare */
int ibool_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    ibool *l = icast(ibool, lfs);
    ibool *r = icast(ibool, rfs);
    return *l == *r;
}
/* ibool: meta-assign */
void ibool_assign(const struct imeta *meta, iptr dst, const iptr src) {
    ibool *l = icast(ibool, dst);
    ibool *r = icast(ibool, src);
    *l = *r;
}

/* iptr: meta-hash */
int64_t iptr_hash(const struct imeta *meta, const iptr o) {
    int64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* iptr: meta-compare */
int iptr_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    iptr *l = icast(iptr, lfs);
    iptr *r = icast(iptr, rfs);
    return l - r;
}
/* iptr: meta-assign */
void iptr_assign(const struct imeta *meta, iptr dst, const iptr src) {
    iptr *l = icast(iptr, dst);
    iptr *r = icast(iptr, src);
    *l = *r;
}

/* pod destructor */
void ipod_destructor(const struct imeta *meta, iptr o) {
    ipod *p = icast(ipod, o);
    if (p->ptr != p->stbuf) {
        ifree(p->ptr);
        p->ptr = p->stbuf;
    }
}
/* ipod: meta-hash */
int64_t ipod_hash(const struct imeta *meta, const iptr o) {
    ipod *pod = icast(ipod, o);
    imd5 md5;
    imd5reset(&md5);
    imd5write(&md5, (unsigned char*)pod->ptr, pod->size);
    return imd5sum(&md5);
}
/* ipod: meta-compare */
int ipod_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    ipod *l = icast(ipod, lfs);
    ipod *r = icast(ipod, rfs);
    return memcmp(l->ptr, r->ptr, l->size);
}
/* ipod: meta-assign */
void ipod_assign(const struct imeta *meta, iptr dst, const iptr src) {
    ipod *l = icast(ipod, dst);
    ipod *r = icast(ipod, src);
    ipod_destructor(meta, dst);
    if (r->size > sizeof(r->stbuf)) {
        l->ptr = icalloc(1, r->size);
    }
    memcpy(l->ptr, r->ptr, r->size);
}

/* irune: meta-hash */
int64_t irune_hash(const struct imeta *meta, const iptr o) {
    int64_t d = 0;
    memcpy(&d, o, meta->size);
    return d;
}
/* irune: meta-compare */
int irune_compare(const struct imeta *meta, const iptr lfs, const iptr rfs) {
    irune *l = icast(irune, lfs);
    irune *r = icast(irune, rfs);
    return *l - *r;
}
/* irune: meta-assign */
void irune_assign(const struct imeta *meta, iptr dst, const iptr src) {
    irune *l = icast(irune, dst);
    irune *r = icast(irune, src);
    *l = *r;
}

