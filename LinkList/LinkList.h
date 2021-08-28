/*
 * @Author: yonghang.qin
 * @Date: 2021-08-28 10:52:58
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-28 16:01:20
 * @Description:
 */
#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef int DataType;

#include <stdbool.h>

typedef struct LinkList LinkList;

LinkList *LinkListCreate(void);

void LinkListDestroy(LinkList *list);

int LinkListLength(LinkList *list);

bool LinkListEmpty(LinkList *list);

bool LinkListInsert(LinkList *list, int i, DataType data);

static inline bool LinkListInsertBack(LinkList *list, DataType data)
{
    return LinkListInsert(list, LinkListLength(list), data);
}

bool LinkListDelete(LinkList *list, int i, DataType *data);

static inline bool LinkListDeleteBack(LinkList *list, DataType *data)
{
    return LinkListDelete(list, LinkListLength(list) - 1, data);
}

bool LinkListSet(LinkList *list, int i, DataType data);

bool LinkListGet(LinkList *list, int i, DataType *data);

void LinkListMove(LinkList *list, int i);

bool LinkListEnd(LinkList *list);

void LinkListNext(LinkList *list);

DataType LinkListCurrent(LinkList *list);

#define LinkListForEach(list) for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))

#define LinkListEntry(list) LinkListCurrent(list)

int LinkListFind(LinkList *list, DataType data);

#ifdef __cplusplus
}
#endif

#endif
