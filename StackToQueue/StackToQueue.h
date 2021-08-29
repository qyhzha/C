/*
 * @Author: yonghang.qin
 * @Date: 2021-08-29 23:01:51
 * @LastEditors: yonghang.qin
 * @LastEditTime: 2021-08-29 23:42:01
 * @Description: 
 */
#ifndef __STACKTOQUEUE_H__
#define __STACKTOQUEUE_H__

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