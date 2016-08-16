#ifndef _IREFLIST_H_
#define _IREFLIST_H_

#include "foundation/core/iref.h"

typedef struct ireflist {
    int i;
}ireflist;


/* 节点 */
typedef struct irefjoint {
    /* 附加的对象 */
    iref *value;
    
    /* 附加在上的 资源*/
    void *res;
    
    /* 必要的校验 */
    struct ireflist *list;
    
    /* 列表节点 */
    struct irefjoint *next;
    struct irefjoint *pre;
}irefjoint;

/* 构造列表节点 */
irefjoint* irefjointmake(iref *value);

/* 释放列表节点 */
void irefjointfree(irefjoint* joint);

/* 释放附加在列表节点上的资源 */
typedef void (*irefjoint_entry_res_free)(irefjoint *joint);

/* 创建列表 */
ireflist *ireflistmake();

/* 释放列表 */
void ireflistfree(ireflist *list);

/* 创建列表 */
ireflist *ireflistmakeentry(irefjoint_entry_res_free entry);

/* 获取列表长度 */
size_t ireflistlen(const ireflist *list);

/* 获取第一个节点 */
irefjoint* ireflistfirst(const ireflist *list);

/* 从列表里面查找第一个满足要求的节点 */
irefjoint* ireflistfind(const ireflist *list,
                        const iref *value);

/* 往列表增加节点: 前置节点 */
irefjoint* ireflistaddjoint(ireflist *list, irefjoint * joint);

/* 往列表增加节点: 前置节点(会增加引用计数) */
irefjoint* ireflistadd(ireflist *list, iref *value);

/* 往列表增加节点: 前置节点(会增加引用计数) */
irefjoint* ireflistaddres(ireflist *list, iref *value, void *res);

/* 从节点里面移除节点, 返回下一个节点 */
irefjoint* ireflistremovejoint(ireflist *list, irefjoint *joint);
/* 从节点里面移除节点 , 并且释放当前节点, 并且返回下一个节点 */
irefjoint* ireflistremovejointandfree(ireflist *list, irefjoint *joint);
/* 从节点里面移除节点: 并且会释放节点, 返回下一个节点 */
irefjoint* ireflistremove(ireflist *list, iref *value);

/* 释放所有节点 */
void ireflistremoveall(ireflist *list);


#endif