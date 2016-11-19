#include "foundation/container/ineighbor.h"

/* ineighbor destructor */
void ineighbor_destructor(iptr x, iobj *o) {
    ineighbor *neighbor = icast(ineighbor, __irobj(o));
    ineighborclean(neighbor);
}

/* set the relation entry in graphics */
void ineighborbuild(ineighbor *neighbors, ientryrefjointresrelease entry) {
    icheck(neighbors);
    neighbors->neighbors_resfree = entry;
}

/* remove the node from the graphics */
void ineighborclean(ineighbor *node) {
    irefjoint* joint = NULL;
    ineighbor *neighbor = NULL;
    icheck(node);
    
    /* disconnect to others */
    joint = ireflistfirst(node->neighbors_to);
    while (joint) {
        neighbor = icast(ineighbor, joint->value);
        ireflistremove(neighbor->neighbors_from, irefcast(node));
        joint = joint->next;
    }
    iassign(node->neighbors_to, NULL);
    
    /* disconnect from others */
    joint = ireflistfirst(node->neighbors_from);
    while (joint) {
        neighbor = icast(ineighbor, joint->value);
        ireflistremove(neighbor->neighbors_to, irefcast(node));
        joint = joint->next;
    }
    iassign(node->neighbors_from, NULL);
}

/* graphics: add a edge-way */
void ineighboradd(ineighbor *from, ineighbor *to) {
    ineighboraddvalue(from, to, NULL, NULL);
}

/* graphics: add a edge-way with value append */
void ineighboraddvalue(ineighbor *from, ineighbor *to, void *from_to, void *to_from) {
    icheck(from);
    icheck(to);
    
    if (!from->neighbors_to) {
        from->neighbors_to = ireflistmakeentry(from->neighbors_resfree);
    }
    ireflistaddres(from->neighbors_to, irefcast(to), from_to);
    if (!to->neighbors_from) {
        to->neighbors_from = ireflistmakeentry(to->neighbors_resfree);
    }
    ireflistaddres(to->neighbors_from, irefcast(from), to_from);
}

/* graphics: delete a edge-way */
void ineighbordel(ineighbor *from, ineighbor *to) {
    ireflistremove(from->neighbors_to, irefcast(to));
    ireflistremove(to->neighbors_from, irefcast(from));
}

/* graphics: in */
size_t ineighborindegree(ineighbor *node) {
    icheckret(node, 0);
    return ireflistlen(node->neighbors_from);
}

/* graphics: out */
size_t ineighboroutdegree(ineighbor *node) {
    icheckret(node, 0);
    return ireflistlen(node->neighbors_to);
}
