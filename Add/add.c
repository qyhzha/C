#include <stdio.h>

int add(int a, int b)
{
    int ret = 0;
    int and = a & b;
    int or = a ^ b;

    while (and)
    {
        ret = and << 1;

        and = ret & or;
        or = ret ^ or;
    }

    ret = or;

    return ret;
}

int main()
{
    int a = 0x2067, b = 0x0a24;

    printf("a + b = %d or %d\r\n", a + b, add(a, b));

    return 0;
}