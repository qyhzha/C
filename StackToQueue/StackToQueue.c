#include <stdlib.h>
#include "Stack.h"
#include "StackToQueue.h"

struct Queue
{
    Stack *stack1;
    Stack *stack2;
    int m_length;
};

Queue *QueueCreate(void) //O(n)
{
    Queue *ret = (Queue *)malloc(sizeof(Queue));
    if (ret == NULL)
    {
        return NULL;
    }

    ret->stack1 = StackCreate();
    ret->stack2 = StackCreate();

    if ((ret->stack1 == NULL) || (ret->stack2 == NULL))
    {
        StackDestroy(ret->stack1);
        StackDestroy(ret->stack2);

        free(ret);

        return NULL;
    }

    ret->m_length = 0;

    return ret;
}

void QueueDestroy(Queue *queue) //O(n)
{
    if (queue != NULL)
    {
        StackDestroy(queue->stack1);
        StackDestroy(queue->stack2);

        free(queue);
    }
}

int QueueLength(Queue *queue) //O(1)
{
    return (queue != NULL) ? queue->m_length : -1;
}

bool QueueEnqueue(Queue *queue, DataType data) //O(1)
{
    return (queue != NULL) && StackPush(queue->stack1, data) && ++queue->m_length;
}

bool QueueDequeue(Queue *queue, DataType *data) //O(n)
{
    bool ret = (queue != NULL);

    if (ret)
    {
        while (StackLength(queue->stack1) > 0)
        {
            DataType temp;
            ret = ret && StackPop(queue->stack1, &temp);
            ret = ret && StackPush(queue->stack2, temp);
        }

        ret = ret && StackPop(queue->stack2, data);

        while (StackLength(queue->stack2) > 0)
        {
            DataType temp;
            ret = ret && StackPop(queue->stack2, &temp);
            ret = ret && StackPush(queue->stack1, temp);
        }

        if (ret)
        {
            queue->m_length--;
        }
    }

    return ret;
}

bool QueueFront(Queue *queue, DataType *data) //O(n)
{
    bool ret = (queue != NULL);

    if (ret)
    {
        while (StackLength(queue->stack1) > 0)
        {
            DataType temp;
            ret = ret && StackPop(queue->stack1, &temp);
            ret = ret && StackPush(queue->stack2, temp);
        }

        ret = ret && StackTop(queue->stack2, data);

        while (StackLength(queue->stack2) > 0)
        {
            DataType temp;
            ret = ret && StackPop(queue->stack2, &temp);
            ret = ret && StackPush(queue->stack1, temp);
        }
    }

    return ret;
}