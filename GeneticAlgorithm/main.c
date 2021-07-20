#include <stdio.h>
#include "GeneticAlgorithm.h"

static double calculate(double x)
{
    //测试用多项式
    return x*(x*(x*(x*(x*(x-10)-26)+344)+193)-1846)-1680;
}

int main()
{
    result_t result;
    int i;

    for (i = 0; i < 10; i++)
    {
        result = solution(-8, 8, calculate);
        printf("当取值x = %lf时, 表达式y=x^6-10x^5-26x^4+344x^3+193x^2-1846x-1680达到最小值:\ny = %lf\n", result.x, result.y);
    }

    return 0;
}
