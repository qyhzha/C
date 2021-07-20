#ifndef __GENETICALGORITHM_H__
#define __GENETICALGORITHM_H__

#define SUM         20          //种群数目
#define MAXloop     400         //最大循环次数
#define error       0.00001     //若两次最优值之差小于此数则认为结果没有改变
#define crossp      0.7         //交叉概率
#define mp          0.04        //变异概率

typedef struct
{
    double x;
    double y;
} result_t;

result_t solution(int min, int max, double(*callback)(double x));

#endif