/*
 * @Author: yonghang.qin
 * @Date: 2021-08-29 23:01:51
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-29 23:11:47
 * @Description: 
 */
#include "Stack.h"
#include <stdio.h>

int main()
{
    Stack *stack = StackCreate();

    if (stack != NULL)
    {
        int i, len = -1, data = -1;

        for (i = 0; i < 20; i++)
        {
            StackPush(stack, i);
        }

        len = StackLength(stack);
        printf("length = %d\n", len);

        for (i = 0; i < 10; i++)
        {
            StackPop(stack, NULL);
        }

        len = StackLength(stack);
        printf("length = %d\n", len);

        printf("begin print\n");
        for (i = 0; i < len; i++)
        {
            StackPop(stack, &data);

            printf("stack[%02d] = %-2d\n", i, data);
        }
        printf("end print\n");

        printf("get top = %d\n", StackTop(stack, &data));

        StackDestroy(stack);
    }

    return 0;
}