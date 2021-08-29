/*
 * @Author: yonghang.qin
 * @Date: 2021-08-29 22:14:37
 * @LastEditTime: 2021-08-29 22:52:08
 * @LastEditors: yonghang.qin
 * @Description: In User Settings Edit
 */
#include "Queue.h"
#include <stdio.h>

int main()
{
    Queue *queue = QueueCreate();

    if (queue != NULL)
    {
        int i, len = -1, data = -1;

        for (i = 0; i < 100; i++)
        {
            QueueEnqueue(queue, i);
        }

        len = QueueLength(queue);
        printf("len = %d\n", len);

        for (i = 0; i < len / 2; i++)
        {
            QueueDequeue(queue, NULL);
        }

        len = QueueLength(queue);
        printf("len = %d\n", len);

        printf("begin print\n");
        for (i = 0; i < len; i++)
        {
            QueueDequeue(queue, &data);
            printf("queue[%02d] = %-2d\n", i, data);
        }
        printf("end print\n");

        printf("get front = %d\n", QueueFront(queue, &data));

        QueueDestroy(queue);
    }

    return 0;
}