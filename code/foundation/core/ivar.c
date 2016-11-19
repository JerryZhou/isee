#include "foundation/core/ivar.h"
#include "foundation/core/imeta.h"
#include "foundation/core/imetatypes.h"

    
/* ivar destructor */
void ivar_destructor(iptr x, iobj *o) {
    ivar *var = icast(ivar, __irobj(o));
    if (var->meta == imetaof(int) || var->meta == imetaof(int64_t)) {
        
    } else if(var->meta == imetaof(ipod)) {
        
    } else if(var->meta == imetaof(iptr)) {
        
    } else if(var->meta == imetaof(iref)) {
        irefdelete(var->v.ref);
    }
}
 
