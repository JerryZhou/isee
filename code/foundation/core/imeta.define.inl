/* declare all the types for user defines */
#include "foundation/core/imetatypes.h"

/* for foundation types */
#undef __ideclaremeta
#undef __ideclaremetacapacity
#undef __ideclaremetapart
#undef __ideclaremetafull
/* name, size, capacity, mthis, constructor, destructor, hash, compare */
#define __ideclaremetafull(type, cap, constructor, destructor, hash, compare) {#type, sizeof(type), cap, NULL, constructor, destructor, hash, compare }
#define __ideclaremetapart(type, cap, constructor, destructor) __ideclaremetafull(type, cap, constructor, destructor, NULL, NULL)
#define __ideclaremetacapacity(type, cap) __ideclaremetapart(type, cap, NULL, NULL)
#define __ideclaremeta(type) __ideclaremetacapacity(type, 0)


/* for user types */
#undef __iudeclaremeta
#undef __iudeclaremetacapacity
#undef __iudeclaremetapart
#undef __iudeclaremetafull

#define __iudeclaremeta(type) irealdeclareregister(type)
#define __iudeclaremetacapacity(type, capacity) irealdeclareregister(type)
#define __iudeclaremetapart(type, capacity, constructor, destructor) irealdeclareregister(type)
#define __iudeclaremetafull(type, capacity, constructor, destructor, hash, compare) irealdeclareregister(type)
