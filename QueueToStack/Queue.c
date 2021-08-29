/*
 * @Author: yonghang.qin
 * @Date: 2021-08-28 10:49:49
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-29 22:53:35
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
    if (queue == NULL)
    {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        return false;
    }

    node->m_data = data;

    add(queue->m_pre, (Node *)queue, node);

    queue->m_length++;

    return true;
}

bool QueueDequeue(Queue *queue, DataType *data)
{
    if (QueueLength(queue) < 1)
    {
        return false;
    }

    Node *node = queue->m_next;

    if (data != NULL)
    {
        *data = node->m_data;
    }

    delete(node->m_pre, node->m_next);

    queue->m_length--;

    free(node);

    return true;
}

bool QueueFront(Queue *queue, DataType *data)
{
    if (QueueLength(queue) < 1 || data == NULL)
    {
        return false;
    }

    *data = queue->m_next->m_data;

    return true;
}