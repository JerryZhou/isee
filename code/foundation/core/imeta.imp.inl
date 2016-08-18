/* declare all the types for user defines */
#include "foundation/core/imetatypes.h"

/* for user types */
#undef __iudeclaremeta
#undef __iudeclaremetacapacity
#undef __iudeclaremetapart
#undef __iudeclaremetafull

#define __iudeclaremetafull(type, capacity, constructor, destructor, hash, compare) irealimplementregisterfull(type, capacity, constructor, destructor, hash, compare)
#define __iudeclaremetapart(type, capacity, constructor, destructor) __iudeclaremetafull(type, capacity, constructor, destructor, NULL, NULL)
#define __iudeclaremetacapacity(type, capacity) __iudeclaremetapart(type, capacity, NULL, NULL)
#define __iudeclaremeta(type) __iudeclaremetacapacity(type, 0)

#define __iudeclare imetaconfig config