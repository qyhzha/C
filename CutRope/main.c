#include <stdio.h>
#include <stdlib.h>

void cut(int number, int *space, int length)
{
    if (length > 0)
    {
        *space = number / length;
        cut(number - *space, space + 1, length - 1);
    }
}

int mul(int *space, int length)
{
    if (space && length > 0)
    {
        int number = 1;

        for (int i = 0; i < length; i++)
        {
            number = number * space[i];
        }

        return number;
    }

    return 0;
}

int cutRope(int number)
{
    int ret = -1;
    for (int i = 1; i <= number; i++)
    {
        int *space = (int *)malloc(sizeof(int) * i);

        cut(number, space, i);
        int total = mul(space, i);

        free(space);

        ret = (ret > total) ? ret : total;
    }

    return ret;
}

int main()
{
    int total = cutRope(15);

    printf("total(%d)", total);

    return 0;
}
