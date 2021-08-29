/*
 * @Author: yonghang.qin
 * @Date: 2021-08-28 10:49:49
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-29 23:16:49
 * @Description:
 */
#include <stdlib.h>
#include "Stack.h"

typedef struct Node
{
    struct Node *m_pre;
    struct Node *m_next;
    DataType m_data;
} Node;

struct Stack
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

Stack *StackCreate(void)
{
    Stack *ret = (Stack *)malloc(sizeof(Stack));

    if (ret != NULL)
    {
        ret->m_pre = (Node *)ret;
        ret->m_next = (Node *)ret;
        ret->m_length = 0;
    }

    return ret;
}

void StackDestroy(Stack *stack)
{
    if (stack != NULL)
    {
        while (StackLength(stack) > 0)
        {
            StackPop(stack, NULL);
        }

        free(stack);
    }
}

int StackLength(Stack *stack)
{
    return (stack != NULL) ? stack->m_length : -1;
}

bool StackPush(Stack *stack, DataType data)
{
    if (stack == NULL)
    {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        return false;
    }

    node->m_data = data;

    add((Node *)stack, stack->m_next, node);

    stack->m_length++;

    return true;
}

bool StackPop(Stack *stack, DataType *data)
{
    if (StackLength(stack) < 1)
    {
        return false;
    }

    Node *node = stack->m_next;

    if (data != NULL)
    {
        *data = node->m_data;
    }

    delete(node->m_pre, node->m_next);

    stack->m_length--;

    free(node);

    return true;
}

bool StackTop(Stack *stack, DataType *data)
{
    if (StackLength(stack) < 1 || data == NULL)
    {
        return false;
    }

    *data = stack->m_next->m_data;

    return true;
}