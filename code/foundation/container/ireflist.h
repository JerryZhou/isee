#ifndef _IREFLIST_H_
#define _IREFLIST_H_

#include "foundation/core/iref.h"
#include "foundation/core/iwref.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* ireflist-joint */
typedef struct irefjoint {
    irefdeclare;
    
    /* joint-value */
    iref *value;
    
    /* joint-res: mapping the value to res */
    void *res;
    
    /* the joined list */
    iwref *list;
    
    /* double linked list: next and pre */
    struct irefjoint *next;
    struct irefjoint *pre;
}irefjoint;

/* refjoint destructor */
void irefjoint_destructor(ithis x, iobj *o);
    
/* make a joint */
irefjoint* irefjointmake(iref *value);

/* release the joint */
void irefjointfree(irefjoint* joint);

/* entry to release the joint res */
typedef void (*ientryrefjointresrelease)(irefjoint *joint);

/* reflist */
typedef struct ireflist {
    irefdeclare;
    
    /* root node of list */
    irefjoint *root;
    /* the length of list */
    size_t length;
    /* the tick the list changed */
    int64_t tick;
    /* free the res append in list */
    ientryrefjointresrelease entry;
}ireflist;

/* destructor for ireflist */
void ireflist_destructor(ithis x, iobj *o);

/* make a default reflist with resource NULL */
ireflist *ireflistmake();

/* make a reflist with resource-manager */
ireflist *ireflistmakeentry(ientryrefjointresrelease entry);

/* get the list length */
size_t ireflistlen(const ireflist *list);

/* get the list first node */
irefjoint* ireflistfirst(const ireflist *list);

/* find the node in list with first match */
irefjoint* ireflistfind(const ireflist *list,
                        const iref *value);

/* add node to list: insert before, 
 * the return value should be retain by yourself if you want to hold it */
irefjoint* ireflistaddjoint(ireflist *list, irefjoint * joint);

/* add value to list: insert before,
 * the return value should be retain by yourself if you want to hold it */
irefjoint* ireflistadd(ireflist *list, iref *value);

/* add value and res to list: insert before
 * the return value should be retain by yourself if you want to hold it */
irefjoint* ireflistaddres(ireflist *list, iref *value, void *res);

/* remove joint from the list and return the next joint */
irefjoint* ireflistremovejoint(ireflist *list, irefjoint *joint);
/* remove the first joint with the right value, then return the next joint */
irefjoint* ireflistremove(ireflist *list, iref *value);

/* remove all of joints in the list */
void ireflistremoveall(ireflist *list);

    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif