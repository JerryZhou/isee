#ifndef _IKVCACHE_H_
#define _IKVCACHE_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
    /* forward declares */
    struct idict;
    struct ireflist;
    struct ivar;
    
    /* the control flag in kv-cache */
    typedef enum EnumKvCacheFlag {
        EnumKvCacheFlag_NotTrimTheRetained = 1,      /* do not trime the retained object */
        
    } EnumKvCacheFlag;
    
    /* the const lru-memory-cache */
    typedef struct ikvcache {
        irefdeclare;
        
        int flag;
        
        struct idict *dict;             /* the key-value */
        struct ireflist *lru;           /* the lru node list */
    } ikvcache;
    
    /**/
    ikvcache* ikvcachemake(size_t capacity);
    
    /* destructor */
    void ikvcache_destructor(const struct imeta*, iptr o);
    
    /**/
    void ikvcacheclear(ikvcache* cache);
    
    /**/
    size_t ikvcachetrim(ikvcache* cache, size_t trim);
    
    /**/
    struct ivar * ikvcacheget(const ikvcache* cache, const struct ivar* key);
    
    /**/
    void ikvcacheput(struct ikvcache* cache, const struct ivar *key, struct ivar *value);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IKVCACHE_H_ */
