/*
 * @Author: yonghang.qin
 * @Date: 2021-08-28 10:49:49
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-28 18:14:15
 * @Description:
 */
#include <stdlib.h>
#include "Queue.h"

typedef struct Node
{
    struct Node *m_pre;
    struct Node *m_next;
    DataType m_data;
} Node;

struct Queue
{
    struct Node *m_pre;
    struct Node *m_next;
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

Queue *QueueCreate(void)
{
    Queue *ret = (Queue *)malloc(sizeof(Queue));

    if (ret != NULL)
    {
        ret->m_pre = (Node *)ret;
        ret->m_next = (Node *)ret;
        ret->m_length = 0;
    }

    return ret;
}

void QueueDestroy(Queue *queue)
{
    if (queue != NULL)
    {
        while (QueueLength(queue) > 0)
        {
            QueueDequeue(queue, NULL);
        }

        free(queue);
    }
}

int QueueLength(Queue *queue)
{
    return (queue != NULL) ? queue->m_length : -1;
}

bool QueueEnqueue(Queue *queue, DataType data)
{

}

bool QueueDequeue(Queue *queue, DataType *data);
bool QueueFront(Queue *queue, DataType *data);

DynamicQueue *DynamicQueueCreate(void)//O(1)
{
    DynamicQueue *ret = MALLOC(DynamicQueue, 1);

    if (ret != NULL)
    {
        ret->list = LinkListCreate(); //O(1)

        if (ret->list != NULL)
        {
            ret->len = 0;
        }
        else
        {
            free(ret);
            ret = NULL;
        }
    }

    return ret;
}

DynamicQueue *DynamicQueueDestroy(DynamicQueue *queue)				//O(n)
{
    if (queue != NULL)
    {
        LinkListDestroy(queue->list);	//O(n)
        free(queue);
    }

    return NULL;
}

int DynamicQueueLength(DynamicQueue *queue)							//O(1)
{
    return (queue != NULL) ? queue->len : -1;
}

Bool DynamicQueueEnqueue(DynamicQueue *queue, DataType data)		//O(n)
{
    Bool ret = (queue != NULL);

    if (ret)
    {
        ret = LinkListInsert(queue->list, queue->len, data);//O(n)
        if (ret) queue->len++;
    }

    return ret;
}

Bool DynamicQueueDequeue(DynamicQueue *queue, DataType *data)		//O(1)
{
    Bool ret = (queue != NULL);

    if (ret)
    {
        ret = LinkListDelete(queue->list, 0, data);	//O(1)
        if (ret) queue->len--;
    }
}

Bool DynamicQueueFront(DynamicQueue *queue, DataType *data)			//(1)
{
    Bool ret = (queue != NULL) && (data != NULL);

    if (ret)
    {
        ret = LinkListGet(queue->list, 0, data);
    }

    return ret;
}