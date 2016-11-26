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
