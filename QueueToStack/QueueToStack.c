#include <stdlib.h>
#include "Queue.h"
#include "QueueToStack.h"

struct Stack
{
    Queue *queue1;
    Queue *queue2;
    int m_length;
};

Stack *StackCreate(void) //O(1)
{
    Stack *ret = (Stack *)malloc(sizeof(Stack));
    if (ret == NULL)
    {
        return NULL;
    }

    ret->queue1 = QueueCreate();
    ret->queue2 = QueueCreate();

    if ((ret->queue1 == NULL) || (ret->queue2 == NULL))
    {
        QueueDestroy(ret->queue1);
        QueueDestroy(ret->queue2);

        free(ret);

        return NULL;
    }

    ret->m_length = 0;

    return ret;
}

void StackDestroy(Stack *stack) //O(n)
{
    if (stack != NULL)
    {
        QueueDestroy(stack->queue1);
        QueueDestroy(stack->queue2);

        free(stack);
    }
}

int StackLength(Stack *stack) //O(1)
{
    return (stack != NULL) ? stack->m_length : -1;
}

bool StackPush(Stack *stack, DataType data) //O(n)
{
    return (stack != NULL) && QueueEnqueue(stack->queue1, data) && ++stack->m_length;
}

bool StackPop(Stack *stack, DataType *data) //O(n)
{
    bool ret = (stack != NULL);

    if (ret)
    {
        while (QueueLength(stack->queue1) > 1)
        {
            DataType data;
            ret = ret && QueueDequeue(stack->queue1, &data);
            ret = ret && QueueEnqueue(stack->queue2, data);
        }

        ret = ret && QueueDequeue(stack->queue1, data);

        while (QueueLength(stack->queue2) > 0)
        {
            DataType data;
            ret = ret && QueueDequeue(stack->queue2, &data);
            ret = ret && QueueEnqueue(stack->queue1, data);
        }

        if (ret)
        {
            stack->m_length--;
        }
    }

    return ret;
}

bool StackTop(Stack *stack, DataType *data) //O(n)
{
    bool ret = ((stack != NULL) && (data != NULL));

    if (ret)
    {
        while (QueueLength(stack->queue1) > 1)
        {
            DataType data;
            ret = ret && QueueDequeue(stack->queue1, &data);
            ret = ret && QueueEnqueue(stack->queue2, data);
        }

        ret = ret && QueueDequeue(stack->queue1, data);
        ret = ret && QueueEnqueue(stack->queue2, *data);

        while (QueueLength(stack->queue2) > 0)
        {
            DataType data;
            ret = ret && QueueDequeue(stack->queue2, &data);
            ret = ret && QueueEnqueue(stack->queue1, data);
        }
    }

    return ret;
}