#include "foundation/container/ineighbor.h"

SP_SUIT(ineighbor);

typedef struct node_graphics {
    ineighbor *A;
    ineighbor *B;
    ineighbor *C;
    ineighbor *D;
    ineighbor *E;
}node_graphics;

static void _inode_prepare_graphics(node_graphics *g) {
    g->A = irefnew(ineighbor);
    g->B = irefnew(ineighbor);
    g->C = irefnew(ineighbor);
    g->D = irefnew(ineighbor);
    g->E = irefnew(ineighbor);
}

static void _inode_free_graphics(node_graphics *g) {
    irefdelete(g->A);
    irefdelete(g->B);
    irefdelete(g->C);
    irefdelete(g->D);
    irefdelete(g->E);
}

/*
 * A ---> B ---> C ---> D
 *        B ---> E
 * A ---> D
 *                      D ---> B
 *                                  E ---> B
 */
SP_CASE(ineighbor, ineighboradd) {
    node_graphics g;
    _inode_prepare_graphics(&g);
    
    ineighboradd(g.A, g.B);
    
    SP_EQUAL(g.A->neighbors_from, NULL);
    SP_EQUAL(g.B->neighbors_to, NULL);
    SP_EQUAL(ireflistlen(g.A->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.B->neighbors_from), 1);
    SP_EQUAL(ireflistfirst(g.B->neighbors_from)->value, irefcast(g.A));
    SP_EQUAL(ireflistfirst(g.A->neighbors_to)->value, irefcast(g.B));
    
    ineighboradd(g.A, g.D);
    ineighboradd(g.B, g.C);
    ineighboradd(g.B, g.E);
    ineighboradd(g.C, g.D);
    ineighboradd(g.D, g.B);
    ineighboradd(g.E, g.B);
    
    SP_EQUAL(ireflistlen(g.A->neighbors_to), 2)
    SP_EQUAL(ireflistlen(g.A->neighbors_from), 0)
    
    SP_EQUAL(ireflistlen(g.B->neighbors_to), 2)
    SP_EQUAL(ireflistlen(g.B->neighbors_from), 3);
    
    SP_EQUAL(ireflistlen(g.C->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.C->neighbors_from), 1);
    
    SP_EQUAL(ireflistlen(g.D->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.D->neighbors_from), 2);
    
    SP_EQUAL(ireflistlen(g.E->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.E->neighbors_from), 1);
    
    _inode_free_graphics(&g);
}

SP_CASE(ineighbor, ineighbordel) {
    
    node_graphics g;
    _inode_prepare_graphics(&g);
    ineighboradd(g.A, g.B);
    ineighboradd(g.A, g.D);
    ineighboradd(g.B, g.C);
    ineighboradd(g.B, g.E);
    ineighboradd(g.C, g.D);
    ineighboradd(g.D, g.B);
    ineighboradd(g.E, g.B);
    SP_EQUAL(ireflistlen(g.A->neighbors_to), 2)
    SP_EQUAL(ireflistlen(g.A->neighbors_from), 0)
    
    SP_EQUAL(ireflistlen(g.B->neighbors_to), 2)
    SP_EQUAL(ireflistlen(g.B->neighbors_from), 3);
    
    SP_EQUAL(ireflistlen(g.C->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.C->neighbors_from), 1);
    
    SP_EQUAL(ireflistlen(g.D->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.D->neighbors_from), 2);
    
    SP_EQUAL(ireflistlen(g.E->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.E->neighbors_from), 1);
    
    ineighbordel(g.A, g.B);
    SP_EQUAL(ireflistlen(g.A->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.A->neighbors_from), 0)
    
    SP_EQUAL(ireflistlen(g.B->neighbors_to), 2)
    SP_EQUAL(ireflistlen(g.B->neighbors_from), 2);
    
    
    _inode_free_graphics(&g);
}

SP_CASE(ineighbor, ineighborsclean) {
    node_graphics g;
    _inode_prepare_graphics(&g);
    ineighboradd(g.A, g.B);
    ineighboradd(g.A, g.D);
    ineighboradd(g.B, g.C);
    ineighboradd(g.B, g.E);
    ineighboradd(g.C, g.D);
    ineighboradd(g.D, g.B);
    ineighboradd(g.E, g.B);
    
    SP_EQUAL(ineighboroutdegree(g.A), 2);
    SP_EQUAL(ineighborindegree(g.A), 0);
    
    SP_EQUAL(ireflistlen(g.B->neighbors_to), 2);
    SP_EQUAL(ireflistlen(g.B->neighbors_from), 3);
    
    SP_EQUAL(ireflistlen(g.C->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.C->neighbors_from), 1);
    
    SP_EQUAL(ireflistlen(g.D->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.D->neighbors_from), 2);
    
    SP_EQUAL(ireflistlen(g.E->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.E->neighbors_from), 1);
    
    ineighborclean(g.B);
    
    SP_EQUAL(ireflistlen(g.A->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.A->neighbors_from), 0)
    
    SP_EQUAL(ireflistlen(g.B->neighbors_to), 0)
    SP_EQUAL(ireflistlen(g.B->neighbors_from), 0);
    
    SP_EQUAL(ireflistlen(g.C->neighbors_to), 1)
    SP_EQUAL(ireflistlen(g.C->neighbors_from), 0);
    
    SP_EQUAL(ireflistlen(g.D->neighbors_to), 0)
    SP_EQUAL(ireflistlen(g.D->neighbors_from), 2);
    
    SP_EQUAL(ireflistlen(g.E->neighbors_to), 0)
    SP_EQUAL(ireflistlen(g.E->neighbors_from), 0);
    
    _inode_free_graphics(&g);
}

SP_CASE(ineighbor, end) {
    SP_TRUE(1);
}