#include "foundation/container/ireflist.h"
#include "foundation/core/imetatypes.h"
#include "foundation/platform/iplatform.h"

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

/* release all the refs */
static void _irefjoint_release_it(irefjoint *joint) {
    ireflist *list = NULL;
    icheck(joint);
    
    /* release the resouce */
    list = icast(ireflist, iwrefstrong(joint->list));
    if (list && list->entry) {
        list->entry(joint);
        list->tick = igetnextmicro();
        irelease(list);
    }
    /* release the ref-value */
    iassign(joint->value, NULL);
    
    /* weak list ref */
    iassign(joint->list, NULL);
}
/* irefjoint destructor */
void irefjoint_destructor(ithis x, iobj *o) {
    irefjoint *joint = icast(irefjoint, __iref(o));
    _irefjoint_release_it(joint);
}

/* make a joint */
irefjoint* irefjointmake(iref *value) {
    irefjoint *joint = irefnew(irefjoint);
    iassign(joint->value, value);
    return joint;
}

/* release the joint */
void irefjointfree(irefjoint* joint) {
    _irefjoint_release_it(joint);
    
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
    ireflist *list = irefnew(ireflist);
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
    
/* get the list last changed tick */
int64_t ireflisttick(const ireflist *list) {
    icheckret(list, 0);
    return list->tick;
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
    iwref *wlist = iwrefmake(irefcast(list));
    iassign(joint->list, wlist);
    list_add_front(list->root, joint);
    iretain(joint);
    ++list->length;
    list->tick = igetnextmicro();
    
    return joint;
}

/* add value to list: insert before */
irefjoint* ireflistadd(ireflist *list, iref *value) {
    irefjoint *joint = NULL;
    icheckret(list, NULL);
    joint = irefjointmake(value);
    ireflistaddjoint(list, joint);
    irelease(joint); /* already hold by list */
    return joint;
}

/* add value and res to list: insert before */
irefjoint* ireflistaddres(ireflist *list, iref *value, void *res) {
    irefjoint *joint = ireflistadd(list, value);
    icheckret(joint, NULL);
    joint->res = res;
    return joint;
}

/* remove joint from the list and return the next joint */
irefjoint * ireflistremovejoint(ireflist *list, irefjoint *joint) {
    irefjoint *next = NULL;
    icheckret(list, next);
    icheckret(joint, next);
    icheckret(iwrefunsafestrong(joint->list) == irefcast(list), next);
    
    /* next */
    next = joint->next;
    
    /* remove-joint */
    list_remove(list->root, joint);
    --list->length;
    irelease(joint);
    list->tick = igetnextmicro();
    
    return next;
}

/* remove the first joint with the right value, then return the next joint */
irefjoint* ireflistremove(ireflist *list, iref *value) {
    irefjoint *joint = NULL;
    icheckret(list, NULL);
    joint = ireflistfind(list, value);
    return ireflistremovejoint(list, joint);
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

