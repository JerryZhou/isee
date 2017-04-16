#include "foundation/container/itree.h"

/* the convicoent macros */
#define RED EnumTreeNodeColor_Red
#define BLACK EnumTreeNodeColor_Black
#define NIL NULL

/* the Nil Value */
static itreenode* _Nil() {
    static itreenode sNil = {.left=NULL, .right=NULL, .color=EnumTreeNodeColor_Red};
    return &sNil;
}

/* the destructor */
void itreenode_destructor(const imeta *meta, iptr o) {
    itreenode *node = icast(itreenode, o);
    node->left = node->right = NULL;
    iobjassign(imetaof(ivar), &node->value, NULL);
    iobjassign(imetaof(ivar), &node->key, NULL);
 }

/* treenode: grandparent */
static itreenode* _itreenode_grandparent(const itreenode* node) {
    if (node->parent==NULL) {
        return NULL;
    }
    return node->parent->parent;
}

/* treenode: uncle */
static itreenode* _itreenode_uncle(const itreenode* node) {
    itreenode* grand = _itreenode_grandparent(node);
    if (grand == NULL) {
        return NULL;
    }
    if (grand->left == node->parent) {
        return grand->right;
    } else {
        return grand->left;
    }
}

/* treenode: sibling */
static itreenode* _itreenode_sibling(const itreenode* node) {
    if (node->parent->left == node) {
        return node->parent->right;
    }
    return node->parent->right;
}

/* treenode: swap the key and value in node */
static void _itreenode_swap(itreenode *lfs, itreenode *rfs) {
    ivar tmp;
    
    tmp = lfs->key;
    lfs->key = rfs->key;
    rfs->key = tmp;
    
    tmp = lfs->value;
    lfs->value = rfs->value;
    rfs->value = tmp;
}

/* assign the value in node */
static void _itreenode_assignvalue(itreenode *node, const ivar *value) {
   iobjassign(imetaof(ivar), &node->value, value);
}

/* tree-make */
static itreenode* _itreenode_make(const ivar *key, const ivar *value, ibyte color) {
    itreenode *node = iobjmalloc(itreenode);
    node->color = color;
    node->left = node->right = NIL;
    node->parent = NULL;
    iobjassign(imetaof(ivar), &node->key, key);
    iobjassign(imetaof(ivar), &node->value, value);
    return node;
}

/* tree-init */
itree *itreemake(int flag) {
    itree *tree = irefnew(itree);
    tree->flag |= flag;
    return tree;
}

/* tree: rotate-right */
static void _itree_rotateright(itree *tree, itreenode *node) {
    itreenode *gp =  _itreenode_grandparent(node);
    itreenode *fa = node->parent;
    itreenode *y = node->right;
    
    fa->left = y;
    
    if(y != NIL) {
        y->parent = fa;
    }
    node->right = fa;
    fa->parent = node;
    
    if(tree->root == fa)
        tree->root = node;
    node->parent = gp;
    
    if(gp != NULL){
        if(gp->left == fa) {
            gp->left = node;
        } else {
            gp->right = node;
        }
    }
}

/* tree: rotate-left */
static void _itree_rotateleft(itree *tree, itreenode* p) {
    if(p->parent == NULL) {
        tree->root = p;
        return;
    }
    itreenode *gp = _itreenode_grandparent(p);
    itreenode *fa = p->parent;
    itreenode *y = p->left;
    
    fa->right = y;
    
    if(y != NIL) {
        y->parent = fa;
    }
    p->left = fa;
    fa->parent = p;
    
    if(tree->root == fa) {
        tree->root = p;
    }
    p->parent = gp;
    
    if(gp != NULL){
        if(gp->left == fa) {
            gp->left = p;
        } else {
            gp->right = p;
        }
    }
}

/* tree: smallest-child */
static itreenode* _itree_smallestchild(const itree *tree, itreenode *node) {
    itreenode *smallest = node;
    while (smallest->left) {
        smallest = smallest->left;
    }
    return smallest;
}

/* tree: delete-node*/
static void _itree_delete(const itree *tree, itreenode *node) {
    if (!node || node == NIL) {
        return;
    }
    _itree_delete(tree, node->left);
    _itree_delete(tree, node->right);
    iobjfree(node);
}

/* tree: search-node-from the tree*/
static itreenode* _itree_search(const itree *tree, itreenode *p, const ivar *key) {
    icheckret(tree && p, NULL);
    
    int cmp = iobjcompare(key->meta, &p->key, key);
    if (cmp > 0) {
        return _itree_search(tree, p->left, key);
    } else if(cmp < 0){
        return _itree_search(tree, p->right, key);
    } else {
        return p;
    }
}


/* tree: remove-node-from the tree*/
static void _itree_removecase(itree *tree, itreenode *p) {
    if(p->parent == NULL){
        p->color = BLACK;
        return;
    }
    
    itreenode *sibling = _itreenode_sibling(p);
    if(sibling->color == RED) {
        p->parent->color = RED;
        sibling->color = BLACK;
        if(p == p->parent->left) {
            _itree_rotateleft(tree, sibling);
        } else {
            _itree_rotateright(tree, sibling);
        }
    }
    
    sibling = _itreenode_sibling(p);
    if(p->parent->color == BLACK && sibling->color == BLACK
       && sibling->left->color == BLACK && sibling->right->color == BLACK) {
        sibling->color = RED;
        _itree_removecase(tree, p->parent);
    } else if(p->parent->color == RED && sibling->color == BLACK
              && sibling->left->color == BLACK && sibling->right->color == BLACK) {
        sibling->color = RED;
        p->parent->color = BLACK;
    } else {
        if(sibling->color == BLACK) {
            if(p == p->parent->left && sibling->left->color == RED
               && sibling->right->color == BLACK) {
                sibling->color = RED;
                sibling->left->color = BLACK;
                _itree_rotateright(tree, sibling->left);
            } else if(p == p->parent->right && sibling->left->color == BLACK
                      && sibling->right->color == RED) {
                sibling->color = RED;
                sibling->right->color = BLACK;
                _itree_rotateleft(tree, sibling->right);
            }
        }
        sibling = _itreenode_sibling(p);
        sibling->color = p->parent->color;
        p->parent->color = BLACK;
        if(p == p->parent->left){
            sibling->right->color = BLACK;
            _itree_rotateleft(tree, sibling);
        } else {
            sibling->left->color = BLACK;
            _itree_rotateleft(tree, sibling);
        }
    }
}

/* tree: remove-node-from the tree*/
static int _itree_removenode(itree *tree, itreenode *p) {
    icheckret(p && tree, iino);
    /* remove from the node */
    --tree->size;
    
    itreenode *child = p->left == NIL ? p->right : p->left;
    if(p->parent == NULL && p->left == NIL && p->right == NIL){
        iobjfree(p);
        tree->root = NULL;
        return iiyes;
    }
    
    if(p->parent == NULL){
        iobjfree(p);
        child->parent = NULL;
        tree->root = child;
        tree->root->color = EnumTreeNodeColor_Black;
        return iiyes;
    }
    
    if(p->parent->left == p){
        p->parent->left = child;
    } else {
        p->parent->right = child;
    }
    if (child) {
        child->parent = p->parent;
    }
    
    if(child && p->color == EnumTreeNodeColor_Black){
        if(child->color == EnumTreeNodeColor_Red){
            child->color = EnumTreeNodeColor_Black;
        } else {
            _itree_removecase(tree, child);
        }
    }
    
    iobjfree(p);
    return iiok;
}

/* tree remove behavior */
static int itree_remove(itree *tree, itreenode *p, const ivar *key) {
    int cmp = iobjcompare(key->meta, &p->key, key);
    if (cmp > 0) {
        if(p->left == NIL){
            return iino;
        }
        return itree_remove(tree, p->left, key);
    } else if(cmp < 0){
        if(p->right == NIL){
            return iino;
        }
        return itree_remove(tree, p->right, key);
    } else {
        if(p->right == NIL){
            _itree_removenode (tree, p);
            return iiyes;
        }
        itreenode *smallest = _itree_smallestchild (tree, p->right);
        _itreenode_swap(p, smallest);
        _itree_removenode (tree, smallest);
        
        return iiyes;
    }
}

/* add node to tree with right-level */
int _itree_addnode(itree *tree, itreenode *p) {
    ++tree->size;
    if(p->parent == NULL) {
        tree->root = p;
        p->color = BLACK;
        return iiyes;
    }
    
    itreenode *grandparent = _itreenode_grandparent(p);
    itreenode *uncle = _itreenode_uncle(p);
    if(p->parent->color == RED){
        if(uncle && uncle->color == RED) {
            p->parent->color = uncle->color = BLACK;
            grandparent->color = RED;
            _itree_addnode(tree, grandparent);
        } else {
            if(p->parent->right == p && grandparent->left == p->parent) {
                _itree_rotateleft(tree, p);
                _itree_rotateright(tree, p);
                p->color = BLACK;
                p->left->color = p->right->color = RED;
            } else if(p->parent->left == p && grandparent->right == p->parent) {
                _itree_rotateright(tree, p);
                _itree_rotateleft(tree, p);
                p->color = BLACK;
                p->left->color = p->right->color = RED;
            } else if(p->parent->left == p && grandparent->left == p->parent) {
                p->parent->color = BLACK;
                grandparent->color = RED;
                _itree_rotateright(tree, p->parent);
            } else if(p->parent->right == p && grandparent->right == p->parent) {
                p->parent->color = BLACK;
                grandparent->color = RED;
                _itree_rotateleft(tree, p->parent);
            }
        }
    }
    
    return iiyes;
}

/* add key-value to tree */
int _itree_add(itree *tree, itreenode *p, const ivar *key, const ivar *value) {
    int cmp = iobjcompare(imetaof(ivar), &p->key, key);
    if(cmp >= 0){
        /* only one key-value in tree */
        if (cmp == 0 && iflag_is(tree->flag, EnumTreeFlag_Map)) {
            _itreenode_assignvalue(p, value);
            return iino;
        }
        
        /* mulpile values may be */
        if(p->left != NIL)
            return _itree_add(tree, p->left, key, value);
        else {
            p->left = _itreenode_make(key, value, RED);
            p->left->parent = p;
            return _itree_addnode(tree, p->left);
        }
    } else {
        if(p->right != NIL)
            return _itree_add(tree, p->right, key, value);
        else {
            p->right = _itreenode_make(key, value, RED);
            p->right->parent = p;
            return _itree_addnode(tree, p->right);
        }
    }
}

/* find the value:ivar with key */
ivar *itreefind(const itree* tree, const ivar *key) {
    itreenode* node = _itree_search(tree, tree->root, key);
    if (node) {
        return &node->value;
    }
    return NULL;
}
    
/* add the value to tree with key */
int itreeadd(itree* tree, const ivar *key, const ivar *value) {
    if (tree->root == NIL) {
        return _itree_addnode(tree, _itreenode_make(key, value, BLACK));
    } else {
        return _itree_add(tree, tree->root, key, value);
    }
}

/* remove the value with key in tree */
int itreeremove(itree *tree, const ivar *key) {
    return itree_remove(tree, tree->root, key);
}

/* remove all */
int itreeremoveall(itree *tree) {
    _itree_delete(tree, tree->root);
    tree->root = NULL;
    tree->size = 0;
    return iiyes;
}

/* the tree size */
size_t itreesize(itree *tree) {
    return tree->size;
}

/* the destructor */
void itree_destructor(const imeta *meta, iptr o) {
    itree *tree = icast(itree, o);
    itreeremoveall(tree);
}
