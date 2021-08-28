#include <stdlib.h>
#include <string.h>
#include "LinkList.h"

typedef struct Node
{
    struct Node *m_pre;
    struct Node *m_next;
    DataType m_data;
} Node;

struct LinkList
{
    Node *m_pre;
    Node *m_next;
    Node *m_current;
    int m_length;
};

static inline void add(Node *pre, Node *next, Node *node)
{
    node->m_next = next;
    node->m_pre = pre;
    pre->m_next = node;
    next->m_pre = node;
}

static inline void delete(Node *pre, Node *next)
{
    pre->m_next = next;
    next->m_pre = pre;
}

static Node *move(LinkList *list, int i)
{
    Node *node = (Node *)list;

    int j;
    if (i <= LinkListLength(list))
    {
        for (j = -1; j < i; j++)
        {
            node = node->m_next;
        }
    }
    else
    {
        i = LinkListLength(list) - i;
        for (j = 0; j < i; j++)
        {
            node = node->m_pre;
        }
    }

    return node;
}

LinkList *LinkListCreate(void)    //O(1)
{
    LinkList *ret = (LinkList *)malloc(sizeof(LinkList));

    if (ret != NULL)
    {
        ret->m_pre = (Node *)ret;
        ret->m_next = (Node *)ret;
        ret->m_current = (Node *)ret;
        ret->m_length = 0;
    }

    return ret;
}

void LinkListDestroy(LinkList *list)   //O(n)
{
    if (list != NULL)
    {
        while (LinkListLength(list) > 0)
        {
            LinkListDelete(list, 0, NULL);
        }

        free(list);
    }
}

int LinkListLength(LinkList *list)  //O(1)
{
    return (list != NULL) ? list->m_length : -1;
}

bool LinkListEmpty(LinkList *list)  //O(1)
{
    return (LinkListLength(list) == 0);
}

bool LinkListInsert(LinkList *list, int i, DataType data)       //O(n)
{
    if (i < 0 || i > LinkListLength(list))
    {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        return false;
    }

    node->m_data = data;

    Node *pre = move(list, i - 1);
    add(pre, pre->m_next, node);

    list->m_length++;

    return true;
}

bool LinkListDelete(LinkList *list, int i, DataType *data)  //O(n)
{
    if (i < 0 || i >= LinkListLength(list))
    {
        return false;
    }

    Node *node = move(list, i);

    if (data != NULL)
    {
        *data = node->m_data;
    }

    if (node == list->m_current)
    {
        list->m_current = node->m_pre;
    }

    delete(node->m_pre, node->m_next);

    free(node);
    list->m_length--;

    return true;
}

bool LinkListSet(LinkList *list, int i, DataType data)  //O(n)
{
    return ((i >= 0) && (i < LinkListLength(list)))
        ? (move(list, i)->m_data = data, true) : false;
}

bool LinkListGet(LinkList *list, int i, DataType *data) //O(n)
{
    return ((data != NULL) && (i >= 0) && (i < LinkListLength(list)))
        ? (*data = move(list, i)->m_data, true) : false;
}

//下面四个配合使用用于遍历链表，时间复杂度为O(n)
void LinkListMove(LinkList *list, int i)
{
    if ((i >= 0) && (i < LinkListLength(list)))
    {
        list->m_current = move(list, i);
    }
}

bool LinkListEnd(LinkList *list)
{
    return (list != NULL) ? (list->m_current == (Node *)list) : false;
}

void LinkListNext(LinkList *list)
{
    if ((list != NULL) && (list->m_current != NULL))
    {
        list->m_current = list->m_current->m_next;
    }
}

DataType LinkListCurrent(LinkList *list)
{
    DataType ret;

    if ((list != NULL) && (list->m_current != NULL))
    {
        ret = list->m_current->m_data;
    }

    return ret;
}

int LinkListFind(LinkList *list, DataType data) //O(n)
{
    int ret = -1;
    int i = 0;

    LinkListForEach(list)
    {
        if (LinkListEntry(list) == data)
        {
            ret = i;
            break;
        }
        i++;
    }

    return ret;
}
