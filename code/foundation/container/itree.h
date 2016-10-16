#ifndef _TPL_H_
#define _TPL_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iref.h"
#include "foundation/container/ineighbor.h"
#include "foundation/container/irefcache.h"
#include "foundation/container/iarray.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
   
/* the tree basic node */
typedef struct itreenode {
    ineighborsdeclare;
    
    int level;                  /* level in tree*/
    int x, y;                   /* coordinate in tree-grid-system */
    
    uint64_t status;            /* the node status */
    
    struct itreenode *parent;   /* the parent */
    iarray *child;              /* all - childs*/
    uint64_t childtick;         /* the node update tick about the node-child */
    
    ireflist *content;          /* the attached content */
    
    struct itreenode *pre, *next; /* the node sequence */
}itreenode;

/* the basic tree */
typedef struct itree {
    irefdeclare;
    
    /* tree-root */
    itreenode *root;
    
    /* tree-node-cache */
    irefcache *nodecache;
}itree;
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _TPL_H_ */