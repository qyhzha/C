/*
 * @Author: yonghang.qin
 * @Date: 2021-08-29 23:01:51
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-29 23:24:21
 * @Description: 
 */
#ifndef __QUEUETOSTACK_H__
#define __QUEUETOSTACK_H__

typedef int DataType;

#include <stdbool.h>

typedef struct Stack Stack;

Stack *StackCreate(void);
void StackDestroy(Stack *stack);
int StackLength(Stack *stack);
bool StackPush(Stack *stack, DataType data);
bool StackPop(Stack *stack, DataType *data);
bool StackTop(Stack *stack, DataType *data);

#endif
