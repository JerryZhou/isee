#include "foundation/core/ireflist.h"
#include "foundation/core/imetatypes.h"

/* macro: list operators */
#define list_add_front(root, node) \
    do {                           \
        if (root == NULL) {        \
            root = node;           \
        }else {                    \
            node->next = root;     \
            root->pre = node;      \
            root = node;           \
        }                          \
    }while(0)

#define list_remove(root, node)         \
    do {                                \
        if (root == node) {             \
            root = node->next;          \
        }                               \
        if (node->next) {               \
            node->next->pre = node->pre;\
        }                               \
        if (node->pre) {                \
            node->pre->next = node->next;\
        }                                \
        node->pre = NULL;                \
        node->next = NULL;               \
    }while(0)

/* irefjoint destructor */
void irefjoint_destructor(ithis x, iobj *o) {
    irefjoint *joint = icast(irefjoint, __iref(o));
    ireflist *list = NULL;
    icheck(joint);
    irelease(joint->value);
    /* release the resouce */
    list = icast(ireflist, iwrefstrong(joint->list));
    if (list && list->entry) {
        list->entry(joint);
        irelease(list);
    }
}

/* make a joint */
irefjoint* irefjointmake(iref *value) {
    irefjoint *joint = iobjmalloc(irefjoint);
    iassign(joint->value, value);
    iretain(joint);
    return joint;
}

/* release the joint */
void irefjointfree(irefjoint* joint) {
    ireflist *list = NULL;
    icheck(joint);
    irelease(joint->value);
    /* release the resouce */
    list = icast(ireflist, iwrefstrong(joint->list));
    if (list && list->entry) {
        list->entry(joint);
        irelease(list);
    }
    joint->value = NULL;
    joint->res = NULL;
    
    irelease(joint);
}

/* reflist entry for free */
void ireflist_destructor(ithis x, iobj *o) {
    ireflist *list = icast(ireflist, __iref(o));
    
    /* remove all the joint */
    ireflistremoveall(list);
}

/* make list */
ireflist *ireflistmake() {
    ireflist *list = iobjmalloc(ireflist);
    iretain(list);
    return list;
}

/* make list with resource manager */
ireflist *ireflistmakeentry(ientryrefjointresrelease entry) {
    ireflist *list = ireflistmake();
    list->entry = entry;
    return list;
}

/* irelease the list */
void ireflistfree(ireflist *list) {
    irelease(list);
}

/* get the list length */
size_t ireflistlen(const ireflist *list) {
    icheckret(list, 0);
    return list->length;
}

/* get the list first node */
irefjoint* ireflistfirst(const ireflist *list) {
    icheckret(list, NULL);
    return list->root;
}

/* find the node in list with first match */
irefjoint* ireflistfind(const ireflist *list, const iref *value) {
    irefjoint* joint = ireflistfirst(list);
    while(joint) {
        if (joint->value == value) {
            break;
        }
        joint = joint->next;
    }
    return joint;
}

/* add node to list: insert before */
irefjoint* ireflistaddjoint(ireflist *list, irefjoint * joint) {
    joint->list = iwrefmake(irefcast(list));
    list_add_front(list->root, joint);
    ++list->length;
    return joint;
}

/* add value to list: insert before */
irefjoint* ireflistadd(ireflist *list, iref *value) {
    irefjoint *joint = NULL;
    icheckret(list, NULL);
    joint = irefjointmake(value);
    return ireflistaddjoint(list, joint);
}

/* add value and res to list: insert before */
irefjoint* ireflistaddres(ireflist *list, iref *value, void *res) {
    irefjoint *joint = ireflistadd(list, value);
    icheckret(joint, NULL);
    joint->res = res;
    return joint;
}

/* remove joint from list and release the joint reference */
static irefjoint* _ireflistremovejointwithfree(ireflist *list, irefjoint *joint, int withfree) {
    irefjoint *next = NULL;
    icheckret(list, next);
    icheckret(joint, next);
    icheckret(iwrefunsafestrong(joint->list) == irefcast(list), next);
    joint->list = NULL;
    
    next = joint->next;
    
    list_remove(list->root, joint);
    --list->length;
    
    if (withfree) {
        irefjointfree(joint);
    }
    
    return next;
}

/* remove and release current joint from the list, then return the next joint */
irefjoint* ireflistremovejointandfree(ireflist *list, irefjoint *joint) {
    return _ireflistremovejointwithfree(list, joint, 1);
}

/* remove joint from the list and return the next joint */
irefjoint * ireflistremovejoint(ireflist *list, irefjoint *joint) {
    return _ireflistremovejointwithfree(list, joint, 0);
}

/* remove the first joint with the right value, then return the next joint */
irefjoint* ireflistremove(ireflist *list, iref *value) {
    irefjoint *joint = NULL;
    icheckret(list, NULL);
    joint = ireflistfind(list, value);
    return _ireflistremovejointwithfree(list, joint, 1);
}

/* remove all of joints in the list */
void ireflistremoveall(ireflist *list) {
    irefjoint *joint = NULL;
    irefjoint *next = NULL;
    icheck(list);
    joint = ireflistfirst(list);
    while(joint) {
        next = joint->next;
        irefjointfree(joint);
        joint = next;
    }
    list->root = NULL;
    list->length = 0;
}

