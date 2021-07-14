#include "timer.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static const qTimerRef QTIMER_ERROR_REF = 255;

typedef struct
{
    unsigned int initialTime;
    unsigned int rescheduleTime;
    unsigned int currentTime;
    void (*callback)(void *arg);
    void *arg;
    unsigned char inCallback;
    unsigned char toStop;
    unsigned char toDelete;
} qTimer;

static volatile unsigned char timerThreadRun;
static qTimer *timerTable[QTIMER_NUMBER_MAX];

static qTimerRef qTimerGetFreeRef(void)
{
    qTimerRef ret = QTIMER_ERROR_REF;

    int i;
    for (i = 0; i < QTIMER_NUMBER_MAX; i++)
    {
        if (timerTable[i] == 0)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

static void *qTimerThread(void *arg)
{
    while (timerThreadRun)
    {
        int i = 0, time = 0;
        for (i = 0; i < QTIMER_NUMBER_MAX; i++)
        {
            if (timerTable[i] == NULL || timerTable[i]->callback == NULL)
            {
                continue;
            }

            time++;
            timerTable[i]->currentTime += QTIMER_TIME_UNIT;

            if (timerTable[i]->initialTime > 0)
            {
                if (timerTable[i]->currentTime > timerTable[i]->initialTime)
                {
                    timerTable[i]->inCallback = 1;
                    timerTable[i]->callback(timerTable[i]->arg);
                    timerTable[i]->inCallback = 0;
                    timerTable[i]->currentTime = 0;
                    timerTable[i]->initialTime = 0;
                }
            }
            else
            {
                if (timerTable[i]->currentTime > timerTable[i]->rescheduleTime)
                {
                    timerTable[i]->inCallback = 1;
                    timerTable[i]->callback(timerTable[i]->arg);
                    timerTable[i]->inCallback = 0;
                    timerTable[i]->currentTime = 0;
                }
            }

            if (timerTable[i]->toStop)
            {
                timerTable[i]->initialTime = 0;
                timerTable[i]->rescheduleTime = 0;
                timerTable[i]->callback = NULL;
                timerTable[i]->arg = NULL;
                timerTable[i]->toStop = 0;
            }

            if (timerTable[i]->toDelete)
            {
                free(timerTable[i]);
                timerTable[i] = NULL;
                timerTable[i]->toDelete = 0;
                time--;
            }
        }

        if (time <= 0)
        {
            timerThreadRun = 0;
        }

        usleep(QTIMER_TIME_UNIT * 1000);
    }

    return 0;
}

qTimerErroCode qTimerCreate(qTimerRef *timerRef)
{
    if (timerRef == NULL)
    {
        return QTIMER_ERRORCODE_NULL_REF;
    }

    qTimerRef ret;

    ret = qTimerGetFreeRef();
    if (ret == QTIMER_ERROR_REF)
    {
        return QTIMER_ERRORCODE_NO_CREATE;
    }

    qTimer *timer = (qTimer *)malloc(sizeof(qTimer));
    if (timer == NULL)
    {
        return QTIMER_ERRORCODE_NO_MEMORY;
    }

    memset(timer, 0, sizeof(qTimer));

    if (!timerThreadRun)
    {
        pthread_t cid = 0;
        timerThreadRun = 1;
        pthread_create(&cid, NULL, qTimerThread, NULL);
    }

    timerTable[ret] = timer;
    *timerRef = ret;

    return QTIMER_ERRORCODE_OK;
}

qTimerErroCode qTimerDelete(qTimerRef timerRef)
{
    if (timerRef < 0 || timerRef >= QTIMER_NUMBER_MAX || timerTable[timerRef] == NULL)
    {
        return QTIMER_ERRORCODE_ERROR_REF;
    }

    if (timerTable[timerRef]->inCallback)
    {
        timerTable[timerRef]->toDelete = 1;
    }
    else
    {
        free(timerTable[timerRef]);
        timerTable[timerRef] = NULL;
    }

    return QTIMER_ERRORCODE_OK;
}

qTimerErroCode qTimerStart(qTimerRef timerRef, unsigned int initialTime,
    unsigned int rescheduleTime, void (*callback)(void *arg), void *arg)
{
    if (timerRef < 0 || timerRef >= QTIMER_NUMBER_MAX)
    {
        return QTIMER_ERRORCODE_ERROR_REF;
    }

    if (timerTable[timerRef] == NULL)
    {
        return QTIMER_ERRORCODE_NO_CREATE;
    }

    if (initialTime < 0 || rescheduleTime < 0)
    {
        return QTIMER_ERRORCODE_ERROR_PARAM;
    }

    timerTable[timerRef]->initialTime = initialTime;
    timerTable[timerRef]->rescheduleTime = rescheduleTime;
    timerTable[timerRef]->currentTime = 0;
    timerTable[timerRef]->callback = callback;
    timerTable[timerRef]->arg = arg;

    return QTIMER_ERRORCODE_OK;
}

qTimerErroCode qTimerStop(qTimerRef timerRef)
{
    if (timerRef < 0 || timerRef >= QTIMER_NUMBER_MAX)
    {
        return QTIMER_ERRORCODE_ERROR_REF;
    }

    if (timerTable[timerRef] == NULL)
    {
        return QTIMER_ERRORCODE_NO_CREATE;
    }

    if (timerTable[timerRef]->inCallback)
    {
        timerTable[timerRef]->toStop = 1;
    }
    else
    {
        timerTable[timerRef]->initialTime = 0;
        timerTable[timerRef]->rescheduleTime = 0;
        timerTable[timerRef]->currentTime = 0;
        timerTable[timerRef]->callback = NULL;
        timerTable[timerRef]->arg = NULL;
    }

    return QTIMER_ERRORCODE_OK;
}
