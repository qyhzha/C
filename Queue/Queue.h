/*
 * @Author: yonghang.qin
 * @Date: 2021-08-28 10:49:49
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-29 23:37:04
 * @Description:
 */
#ifndef __QUEUE_H_
#define __QUEUE_H_

typedef int DataType;

#include <stdbool.h>

typedef struct Queue Queue;

Queue *QueueCreate(void);
void QueueDestroy(Queue *queue);
int QueueLength(Queue *queue);
bool QueueEnqueue(Queue *queue, DataType data);
bool QueueDequeue(Queue *queue, DataType *data);
bool QueueFront(Queue *queue, DataType *data);

#endif
