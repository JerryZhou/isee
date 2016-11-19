#include "foundation/core/ivar.h"
#include "foundation/core/imeta.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iobj.h"
#include "foundation/memory/imemory.h"

    
/* ivar destructor */
void ivar_destructor(iptr x, iobj *o) {
    ivar *var = icast(ivar, __irobj(o));
    if (var->meta == imetaof(int) ||
        var->meta == imetaof(int64_t) ||
        var->meta == imetaof(uint64_t) ||
        var->meta == imetaof(ireal) ||
        var->meta == imetaof(float) ||
        var->meta == imetaof(double) ||
        var->meta == imetaof(ibyte) ||
        var->meta == imetaof(ibool) ||
        var->meta == imetaof(irune) ) {
        /* nothing todo: pod */
    } else if (var->meta == imetaof(ipod)) {
        if (var->v.pod.ptr != var->v.pod.stbuf) {
            ifree(var->v.pod.ptr);
        }
    } else {
        irefdelete(var->v.ref);
    }
}
 
/* ivar type */
int ivartype(const ivar *var) {
    return var->meta->index;
}

/* ivar type: meta */
const struct imeta *ivarmeta(const ivar *var) {
    return var->meta;
}

/* ivar is right-meta-type */
ibool ivaris(const ivar *var, const struct imeta *meta) {
    return ivarmeta(var) == meta;
}
    
/* ivar copy */
ivar *ivardup(const ivar *var) {
    ivar *nvar = nvar = irefnew(ivar);
    if (var->meta == imetaof(int) ||
        var->meta == imetaof(int64_t) ||
        var->meta == imetaof(uint64_t) ||
        var->meta == imetaof(ireal) ||
        var->meta == imetaof(float) ||
        var->meta == imetaof(double) ||
        var->meta == imetaof(ibyte) ||
        var->meta == imetaof(ibool) ||
        var->meta == imetaof(irune) ) {
        nvar->meta = var->meta;
        nvar->v = var->v;
    } else if (var->meta == imetaof(ipod)) {
        nvar->v = var->v;
        nvar->v.pod.ptr = icalloc(1, var->v.pod.size);
        memcpy(nvar->v.pod.ptr, var->v.pod.ptr, var->v.pod.size);
    } else {
        irefretain(var->v.ref);
        nvar->meta = var->meta;
        nvar->v = var->v;
    }
    return nvar;
}
  
/* ivar hash code */
uint64_t *ivarhashcode(const ivar *var) {
    return var->v.u64;
}

/* ivar make functions: int  */
ivar *ivarmakeint(int i) {
    ivar *var = irefnew(ivar);
    var->v.i = i;
    var->meta = imetaof(int);
    return var;
}
/* ivar make functions: int64_t  */
ivar *ivarmakei64(int64_t i64) {
    ivar *var = irefnew(ivar);
    var->v.i64 = i64;
    var->meta = imetaof(int64_t);
    return var;
}
/* ivar make functions: int  */
ivar *ivarmakeu64(uint64_t u64) {
    ivar *var = irefnew(ivar);
    var->v.u64 = u64;
    var->meta = imetaof(uint64_t);
    return var;
}

/* ivar make functions: int  */
ivar *ivarmakereal(ireal real) {
    ivar *var = irefnew(ivar);
    var->v.real = real;
    var->meta = imetaof(ireal);
    return var;
}

/* ivar make functions: int  */
ivar *ivarmakeptr(iptr *ptr) {
    ivar *var = irefnew(ivar);
    var->v.ptr = ptr;
    var->meta = imetaof(iptr);
    return var;
}

/* ivar make functions: int  */
ivar *ivarmakepod(ipod pod) {
    ivar *var = irefnew(ivar);
    var->v.pod = pod;
    var->meta = imetaof(ipod);
    /* the expanded pod */
    if (pod.ptr != pod.stbuf) {
        var->v.pod.ptr = icalloc(1, pod.size);
        memcpy(var->v.pod.ptr, pod.ptr, pod.size);
    }
    return var;
}

/* ivar make functions: int  */
ivar *ivarmakeref(iref *ref) {
    ivar *var = irefnew(ivar);
    iassign(var->v.ref, ref);
    var->meta = iobjgetmeta(ref);
    return var;
}
 
