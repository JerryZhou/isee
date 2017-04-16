#ifndef _TPL_H_
#define _TPL_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iref.h"
#include "foundation/core/ivar.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* the node-color */
typedef enum EnumTreeNodeColor {
    EnumTreeNodeColor_Red,  /* red-zero : default-color*/
    EnumTreeNodeColor_Black,
} EnumTreeNodeColor;
   
/* the tree basic node */
typedef struct itreenode {
    struct itreenode *parent;       /* the node parent */
    struct itreenode *left, *right;   /* the node sequence */
    
    /* the key-value in node */
    ivar key;
    ivar value;
    
    /* the node-color */
    ibyte color;
    
}itreenode;
   
/* the destructor */
void itreenode_destructor(const imeta *meta, iptr o);

/* the red-black-tree
 https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 https://en.wikipedia.org/wiki/AVL_tree
 https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree
 Space		O(n)
 Search/Insert/Remove		O(log n)
 * Each node is either red or black.
 * The root is black. This rule is sometimes omitted. Since the root can always be changed from red to black, but not necessarily vice versa, this rule has little effect on analysis.
 * All leaves (NIL) are black.
 * If a node is red, then both its children are black.
 * Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes. Some definitions: the number of black nodes from the root to a node is the node's black depth; the uniform number of black nodes in all paths from root to the leaves is called the black-height of the red–black tree.
 */
typedef enum EnumTreeFlag {
    EnumTreeFlag_Map = 1<<5, /* used as the hash-map */
}EnumTreeFlag;
    
typedef struct itree {
    irefdeclare;
    
    /* tree-root */
    itreenode *root;
    
    /* tracing the count of node in tree*/
    size_t size;
    /* the balance-tree: one-key vs one-value */
    int flag;
} itree;
    
/* tree-init */
itree *itreemake(int flag);
    
/* the destructor */
void itree_destructor(const imeta *meta, iptr o);
    
/* find the value:ivar with key */
ivar *itreefind(const itree* tree, const ivar *key);
    
/* add the value to tree with key */
int itreeadd(itree* tree, const ivar *key, const ivar *value);
    
/* remove the value with key in tree */
int itreeremove(itree *tree, const ivar *key);
    
/* remove all */
int itreeremoveall(itree *tree);

/* the tree size */
size_t itreesize(itree *tree);
    
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _TPL_H_ */
