#ifndef _IEIGHBOR_H_
#define _IEIGHBOR_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iref.h"
#include "foundation/container/ireflist.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
   
/*************************************************************/
/* ineighbors                                                */
/* https://en.wikipedia.org/wiki/Directed_graph              */
/*************************************************************/
typedef struct ineighbor {
    irefdeclare;
    /* digraph
     *
     * */
    /* all neighbors connected to this node[other ===> this] */
    ireflist *neighbors_from;
    /* all neighbors can reached from this node [this ===> other] */
    ireflist *neighbors_to;
    
    /* List joint resouce free entry */
    ientryrefjointresrelease neighbors_resfree;
}ineighbor;
    
/*macro declare*/
#define ineighborsdeclare \
    irefdeclare; \
    ireflist *neighbors_from; \
    ireflist *neighbors_to; \
    ientryrefjointresrelease neighbors_resfree
    
/* ineighbor destructor */
void ineighbor_destructor(iptr x, iobj *o);
    
/* set the relation entry in graphics */
void ineighborbuild(ineighbor *neighbors, ientryrefjointresrelease entry);

/* remove the node from the graphics */
void ineighborclean(ineighbor *neighbors);

/* graphics: add a edge-way */
void ineighboradd(ineighbor *from, ineighbor *to);

/* graphics: add a edge-way with value append */
void ineighboraddvalue(ineighbor *from, ineighbor *to, void *from_to, void *to_from);

/* graphics: delete a edge-way */
void ineighbordel(ineighbor *from, ineighbor *to);
    
/* graphics: in */
size_t ineighborindegree(ineighbor *node);

/* graphics: out */
size_t ineighboroutdegree(ineighbor *node);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IEIGHBOR_H_ */
