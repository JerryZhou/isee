#include "foundation/core/iobj.h"
#include "foundation/core/imeta.h"
#include "foundation/itype.h"

/* get the meta of obj */
const struct imeta *iobjgetmeta(iconstptr p) {
    iobj *obj = __iobj(p);
    icheckret(obj, NULL);
    return obj->meta;
}

/* if the obj is what we required */
int iobjistype(iconstptr p, const char* type) {
    const imeta *meta = iobjgetmeta(p);
    icheckret(type, iino);
    icheckret(meta, iino);
    
    if (strlen(type) != strlen(meta->name)) {
        return iino;
    }
    
    if (strncmp(type, meta->name, strlen(meta->name)) == 0) {
        return iiok;
    }
    return iino;
}

/* the obj assign */
void iobjassign(const struct imeta *meta, iptr dst, iconstptr src) {
    icheck(dst != src && dst);
    if (src) {
        if (meta->funcs->assign) {
            /* the user-define assign */
            meta->funcs->assign(meta, dst, src);
        } else {
            /* the plain of data */
            memcpy(dst, src, meta->size);
        }
    } else {
        if (meta->funcs->destructor) {
            /* release the resources */
            meta->funcs->destructor(meta, dst);
        } else {
            /* clear the memory */
            memset(dst, 0, meta->size);
        }
    }
}

/* the hash code */
uint64_t iobjhash(const struct imeta *meta, iconstptr obj) {
    icheckret(obj && meta, 0);
    if (meta->funcs->hash) {
        return meta->funcs->hash(meta, obj);
    }
    return (uint64_t)(obj);
}

/* the compare */
int iobjcompare(const struct imeta *meta, iconstptr lfs, iconstptr rfs) {
    icheckret(!(lfs && !rfs), 1);
    icheckret(!(!lfs && rfs), -1);
    icheckret(lfs != rfs, 0);
    if (meta->funcs->compare) {
        return meta->funcs->compare(meta, lfs, rfs);
    } else {
        return memcmp(lfs, rfs, meta->size);
    }
}


