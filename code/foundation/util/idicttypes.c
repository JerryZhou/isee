#include "foundation/util/idicttypes.h"

/* idict<uint64_t, istring*> */
idictentry* idictadd_u64_istring(idict *d, uint64_t key, istring *value) {
    ivar *keyval = ivarmakeu64(key);
    ivar *valueval = ivarmakeref(irefcast(value));
    idictentry* entry = idictadd(d, keyval, valueval);
    irefdelete(keyval);
    irefdelete(valueval);
    return entry;
}

/* idict<istring*, ibool> */
idictentry* idictadd_istring_ibool(idict *d, istring *key, ibool value) {
    ivar *keyval = ivarmakeref(irefcast(key));
    ivar *valueval = ivarmakebool(value);
    idictentry* entry = idictadd(d, keyval, valueval);
    irefdelete(keyval);
    irefdelete(valueval);
    return entry;
}

/* idict<uint64_t, ?> */
int idictremove_u64(idict *d, uint64_t key) {
    ivar *keyval = ivarmakeu64(key);
    int rdbool = idictremove(d, keyval);
    irefdelete(keyval);
    return rdbool;
}

/* idict<istring, ?> */
int idictremove_istring(idict *d, istring *key){
    ivar *keyval = ivarmakeref(irefcast(key));
    int rdbool = idictremove(d, keyval);
    irefdelete(keyval);
    return rdbool;
}

/* idict<uint64_t, ?> */
int idicthas_u64(idict *d, uint64_t key) {
    ivar *keyval = ivarmakeu64(key);
    int rdbool = idicthas(d, keyval);
    irefdelete(keyval);
    return rdbool;
}
    
/* idict<istring, ?> */
int idicthas_istring(idict *d, istring *key) {
    ivar *keyval = ivarmakeref(irefcast(key));
    int rdbool = idicthas(d, keyval);
    irefdelete(keyval);
    return rdbool;
}





