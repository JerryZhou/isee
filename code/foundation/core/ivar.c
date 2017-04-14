#include "foundation/core/ivar.h"
#include "foundation/core/imeta.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iobj.h"
#include "foundation/memory/imemory.h"
#include "foundation/math/imd5.h"

    
/* ivar destructor */
void ivar_destructor(const imeta* meta, iptr o) {
    ivar *var = icast(ivar, o);
    if (var->meta && var->meta->funcs && var->meta->funcs->destructor) {
        var->meta->funcs->destructor(var->meta, &var->v);
    }
}

/* ivar meta-funcs: hashcode */
uint64_t ivar_hash(const imeta* meta, iconstptr o) {
    ivar *var = icast(ivar, o);
    if (var->meta && var->meta->funcs && var->meta->funcs->hash) {
        return var->meta->funcs->hash(var->meta, &var->v);
    }
    return var->v.u64;
}

/* ivar meta-funcs: compare 
 * todos: may be problems in compare with 64 bit
 */
int ivar_compare(const imeta* varmeta, iconstptr lfs, iconstptr rfs) {
    ivar *l = icast(ivar, lfs);
    ivar *r = icast(ivar, rfs);
    const struct imeta* lmeta = iobjgetmeta(l);
    const struct imeta* rmeta = iobjgetmeta(r);
    const struct imeta* meta = lmeta ? lmeta : rmeta;
    if (meta->funcs && meta->funcs->compare) {
        return meta->funcs->compare(meta, &l->v, &r->v);
    }
    return (int)((char*)lfs - (char*)rfs);
}

/* ivar meta-funcs: assign */
void ivar_assign(const struct imeta* meta, iptr dst, iconstptr src) {
    icheck(dst);
    ivar *nvar = icast(ivar, dst);
    ivar *var = icast(ivar, src);
    if (!nvar->meta && var) {
        nvar->meta = var->meta;
    }
    
    const imeta* valuemeta = nvar->meta;
    
    icheck(valuemeta);
    if (valuemeta->funcs && valuemeta->funcs->assign) {
        valuemeta->funcs->assign(valuemeta, &nvar->v, &var->v);
    }
}

/* ivar type */
int ivartype(const ivar *var) {
    icheckret(var && var->meta, 0);
    return var->meta->index;
}

/* ivar type: meta */
const struct imeta *ivarmeta(const ivar *var) {
    icheckret(var, imetaof(inull));
    icheckret(var->meta, imetaof(inull));
    return var->meta;
}

/* simple ivar */
int ivarissimple(const ivar *var) {
    const struct imeta *meta = ivarmeta(var);
    if (meta == imetaof(int) ||
        meta == imetaof(int64_t) ||
        meta == imetaof(uint64_t) ||
        meta == imetaof(ireal) ||
        meta == imetaof(float) ||
        meta == imetaof(double) ||
        meta == imetaof(ibyte) ||
        meta == imetaof(ibool) ||
        meta == imetaof(irune) ||
        meta == imetaof(iptr) ||
        meta == imetaof(inull)) {
        return iiok;
    }
    return iino;
}

/* ivar is right-meta-type */
ibool ivaris(const ivar *var, const struct imeta *meta) {
    return ivartype(var) == imetaindexof(meta);
}
    
/* ivar copy */
ivar *ivardup(const ivar *var) {
    return ivarmake(var->meta, &var->v);
}

/* make a value */
ivar* ivarmake(const struct imeta* meta, iconstptr value) {
    ivar *var = iobjmalloc(ivar);
    var->meta = meta;
    /* constructor */
    if (meta->funcs && meta->funcs->constructor) {
        meta->funcs->constructor(meta, (iptr)(&var->v));
    }
    /* assign */
    if (meta->funcs && meta->funcs->assign) {
        meta->funcs->assign(meta, &var->v, value);
    }
    return var;
}

/* return the value address */
void *ivarvalue(const ivar *var) {
    icheckret(var, NULL);
    return (void*)(&var->v);
}

/* ivar hash code */
uint64_t ivarhashcode(const ivar *var) {
    return ivar_hash(var->meta, var);
}

/* ivar compare should be the same value-type */
int ivarcompare(const ivar *var, const ivar *nvar) {
    const imeta* valuemeta = nvar ? nvar->meta : (var ? var->meta : NULL);
    if (valuemeta->funcs && valuemeta->funcs->compare) {
        return valuemeta->funcs->compare(valuemeta, &var->v, &nvar->v);
    }
    return var - nvar;
}

/* ivar make functions: int  */
ivar *ivarmakeint(int i) {
    return ivarmake(imetaof(int), &i);
}
/* ivar make functions: int64_t  */
ivar *ivarmakei64(int64_t i64) {
    return ivarmake(imetaof(int64_t), &i64);
}
/* ivar make functions: uint64_t  */
ivar *ivarmakeu64(uint64_t u64) {
    return ivarmake(imetaof(uint64_t), &u64);
}

/* ivar make functions: ireal  */
ivar *ivarmakereal(ireal real) {
    return ivarmake(imetaof(ireal), &real);
}

/* ivar make functions: iptr  */
ivar *ivarmakeptr(iptr ptr) {
    return ivarmake(imetaof(iptr), &ptr);
}

/* ivar make functions: ipod  */
ivar *ivarmakepod(ipod pod) {
    return ivarmake(imetaof(ipod), &pod);
}

/* ivar make functions: irefptr  */
ivar *ivarmakeref(irefptr ref) {
    return ivarmake(imetaof(irefptr), &ref);
}

/* ivar make functions: ibool  */
ivar *ivarmakebool(ibool b) {
    return ivarmake(imetaof(ibool), &b);
}
