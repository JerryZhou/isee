#ifndef _IDICTTYPES_H_
#define _IDICTTYPES_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"

#include "foundation/container/idict.h"
#include "foundation/util/istring.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* idict<uint64_t, istring*> */
idictentry* idictadd_u64_istring(idict *d, uint64_t key, istring *value);

/* idict<istring*, ibool> */
idictentry* idictadd_istring_ibool(idict *d, istring *key, ibool value);
    
/* idict<uint64_t, ?> */
int idictremove_u64(idict *d, uint64_t key);

/* idict<istring, ?> */
int idictremove_istring(idict *d, istring *key);
    
/* idict<uint64_t, ?> */
int idicthas_u64(idict *d, uint64_t key);
    
/* idict<istring, ?> */
int idicthas_istring(idict *d, istring *key);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IDICTTYPES_H_ */
