#ifndef __TIMER_H__
#define __TIMER_H__

#define QTIMER_NUMBER_MAX   (10)
#define QTIMER_TIME_UNIT    (10)

typedef unsigned char qTimerRef;

typedef enum
{
    QTIMER_ERRORCODE_OK,
    QTIMER_ERRORCODE_ERROR_PARAM,
    QTIMER_ERRORCODE_NULL_REF,
    QTIMER_ERRORCODE_ERROR_REF,
    QTIMER_ERRORCODE_NO_MEMORY,
    QTIMER_ERRORCODE_NO_CREATE,
} qTimerErroCode;

qTimerErroCode qTimerCreate(qTimerRef *timerRef);
qTimerErroCode qTimerDelete(qTimerRef timerRef);
qTimerErroCode qTimerStart(qTimerRef timerRef, unsigned int initialTime,
    unsigned int rescheduleTime, void (*callback)(void *arg), void *arg);
qTimerErroCode qTimerStop(qTimerRef timerRef);

#endif
