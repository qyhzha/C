#include "timer.h"
#include <stdio.h>
#include <unistd.h>

void timerCallback(void *arg)
{
    printf("I'm fine.\n");
}

int main()
{
    qTimerErroCode ret;
    qTimerRef timerRef;

    ret = qTimerCreate(&timerRef);
    if (ret != 0)
    {
        printf("create timer error. error code(%d).", ret);
    }

    ret = qTimerStart(timerRef, 0, 2000, timerCallback, NULL);
    if (ret != 0)
    {
        printf("start timer error. error code(%d).", ret);
    }

    sleep(10);

    ret = qTimerStop(timerRef);
    if (ret != 0)
    {
        printf("stop timer error. error code(%d).", ret);
    }

    ret = qTimerDelete(timerRef);
    if (ret != 0)
    {
        printf("delete timer error. error code(%d).", ret);
    }

    return 0;
}
