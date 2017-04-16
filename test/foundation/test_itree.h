#include "foundation/container/itree.h"

SP_SUIT(itree);

SP_CASE(itree, itreemake) {
    itree* tree = itreemake(0);
    SP_TRUE(itreesize(tree) == 0);
    irefdelete(tree);
}

static void _xtadd(itree *t, int k, int v) {
    ivar key = {.meta=imetaof(int), .v={k}};
    ivar value = {.meta=imetaof(int), .v={v}};
    itreeadd(t, &key, &value);
}

static int _xtremove(itree *t, int k) {
    ivar key = {.meta=imetaof(int), .v={k}};
    return itreeremove(t, &key);
}

static int _xtfind(itree *t, int k) {
    ivar key = {.meta=imetaof(int), .v={k}};
    ivar *n = itreefind(t, &key);
    if (n) {
        return ivarcast(n, int);
    }
    return 0;
}

SP_CASE(itree, itreeadd) {
    itree*tree = itreemake(0);
    _xtadd(tree, 1, 100);
    /*
     *                  (1:BLACK)
     */
    SP_TRUE(itreesize(tree) == 1);
    _xtadd(tree, 2, 200);
    /**
     *                    (1:BLACK)
     *                    /       \
     *               (NIL:BLACK)  (2:RED)
     */
    SP_TRUE(itreesize(tree) == 2);
    _xtadd(tree, 2, 201);
    /**
     *    (1(100):BLACK)                     (1(100):BLACK)                 (2(201):BLACK)
     *   /            \                       /       \                     /             \
     *  (NIL:BLACK)  (2(200):RED)  ==>  (NIL:BLACK)   (2(201):BLACK) ==> (1(100):RED)   (2:(200):RED)
     *              /                                 /   \                 /   \          /    \
     *        (2(201):RED)                          NIL    (2:(200):RED)  NIL   NIL      NIL     NIL
     */
    SP_TRUE(itreesize(tree) == 3);
    irefdelete(tree);
}

SP_CASE(itree, itreeremove) {
    itree*tree = itreemake(0);
    _xtadd(tree, 1, 100);
    _xtadd(tree, 2, 200);
    _xtadd(tree, 3, 300);
    SP_TRUE(itreesize(tree)==3);
    
    SP_TRUE(_xtremove(tree, 1) == iiok);
    SP_TRUE(itreesize(tree)==2);
    
    SP_TRUE(_xtremove(tree, 10) == iino);
    SP_TRUE(itreesize(tree)==2);
    
    irefdelete(tree);
}

SP_CASE(itree, itreeremove2) {
    itree*tree = itreemake(0);
    _xtadd(tree, 1, 100);
    _xtadd(tree, 2, 200);
    _xtadd(tree, 3, 300);
    SP_TRUE(itreesize(tree)==3);
    
    SP_TRUE(_xtremove(tree, 2) == iiok);
    SP_TRUE(itreesize(tree)==2);
    
    _xtremove(tree, 1);
    _xtremove(tree, 3);
    SP_TRUE(itreesize(tree)==0);
    
    irefdelete(tree);
}

SP_CASE(itree, itreefind) {
    itree*tree = itreemake(0);
    _xtadd(tree, 1, 100);
    _xtadd(tree, 2, 200);
    _xtadd(tree, 3, 300);
    SP_TRUE(itreesize(tree)==3);
    
    SP_TRUE(_xtfind(tree, 1) == 100);
    SP_TRUE(_xtfind(tree, 2) == 200);
    SP_TRUE(_xtfind(tree, 3) == 300);
    
    tree->flag |= EnumTreeFlag_Map;
    _xtadd(tree, 2, 2000);
    SP_TRUE(_xtfind(tree, 2) == 2000);
    
    irefdelete(tree);
}

#include <map>
#include "foundation/math/irand.h"

static void _i_x_tree_ii(itree *d, int key, int value) {
    ivar keyvar = {.v = {key}, .meta = imetaof(int)};
    ivar valuevar = {.v = {value}, .meta = imetaof(int)};
    itreeadd(d, &keyvar, &valuevar);
}

SP_CASE(itree, benchmark) {
    irand r;
    irandinit(&r, igetcurmicro());
    
    std::map<int, int> stdmap;
    uint64_t micro = igetcurmicro();
    for (int i=0; i<10000; ++i) {
        int key = (int)irandN(&r, std::numeric_limits<int>::max());
        int value = (int)irandN(&r, std::numeric_limits<int>::max());
        stdmap[key] = value;
    }
    ilog("stdmap ===> [%lld]\n", igetcurmicro() - micro);
    
    itree *d = itreemake(EnumTreeFlag_Map);
    micro = igetcurmicro();
    for (int i=0; i<10000; ++i) {
        int key = (int)irandN(&r, std::numeric_limits<int>::max());
        int value = (int)irandN(&r, std::numeric_limits<int>::max());
        _i_x_tree_ii(d, key, value);
    }
    ilog("itree ===> [%lld]\n", igetcurmicro() - micro);
    irefdelete(d);
}

SP_CASE(itree, end) {
    SP_TRUE(1);
}
