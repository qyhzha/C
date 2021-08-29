/*
 * @Author: yonghang.qin
 * @Date: 2021-08-28 10:49:49
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-29 23:09:13
 * @Description:
 */
#ifndef __STACK_H_
#define __STACK_H_

typedef int DataType;

#include <stdbool.h>

typedef struct Stack Stack;

Stack* StackCreate(void);
void StackDestroy(Stack *stack);
int StackLength(Stack *stack);
bool StackPush(Stack *stack, DataType data);
bool StackPop(Stack *stack, DataType *data);
bool StackTop(Stack *stack, DataType *data);

#endif
