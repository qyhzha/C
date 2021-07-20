#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "GeneticAlgorithm.h"

typedef struct
{
	unsigned char crossflag;
    int info;              //染色体结构，用一整型数的后14位作为染色体编码
    double suitability;    //次染色体所对应的适应度函数值
} gen;

static gen gen_result;              //记录最优的染色体
static int
result_unchange_time;    //记录在error前提下最优值为改变的循环次数

static gen gen_group[SUM];     //定义父种群
static gen gen_new[SUM];       //定义交叉产生的子种群

//生成x
static inline int randnum(int min, int max)
{
    srand((unsigned int)time(NULL));
    return rand() % ((max - min) * 1000);
}

static inline double convertionB2D(int x, int min)
{
    return ((double)(x + min * 1000) / 1000);
}

static void quickSort(gen *a, int low, int high)
{
    int i = low, j = high - 1;
    gen temp = a[low];  //取第一个元素为标准数据元素

    while (i < j)
    {
        while ((i < j) && (temp.suitability <= a[j].suitability))
            j--; //在数组的右端扫描
        if (i < j)
        {
            a[i].info = a[j].info;
            a[i].suitability = a[j].suitability;
            i++;
        }

        while ((i < j) && (a[i].suitability < temp.suitability))
            i++; //在数组的左端扫描
        if (i < j)
        {
            a[j].info = a[i].info;
            a[j].suitability = a[i].suitability;
            j--;
        }
    }
    a[i] = temp;

    if (low < i) quickSort(a, low, i - 1); //对左端子集合进行递归
    if (i < high) quickSort(a, j + 1, high); //对右端子集合进行递归
}

static int randbit(int min, int max, int x)		//产生在min与max之间的一个不等于x的随机数
{
    int number;

    do
    {
        srand((unsigned int)time(NULL));
        number = rand() % (max - min) + min;
    } while(number == x);

    return number;
}

static void initiate(int min, int max, double(*callback)(double x))
{
    int i;
    double x;

    for (i = 0 ; i < SUM ; i++)
    {
        gen_group[i].info = randnum(min, max);
        gen_group[i].suitability = callback(convertionB2D(gen_group[i].info, min));
    }

    gen_result.suitability = 1000;
    result_unchange_time = 0;
}

static inline void evaluation(void)
{
    quickSort(gen_group, 0, SUM);
}

static int record(void)    //记录最优解和判断是否满足条件
{
    double x;

    x = gen_result.suitability - gen_group[0].suitability;

    if (x < error && x > -error)
    {
        result_unchange_time++;
    }

    if (result_unchange_time >= 20)
    {
        return 1;
    }

    gen_result.info = gen_group[0].info;
    gen_result.suitability = gen_group[0].suitability;
    result_unchange_time = 0;

    return 0;
}

static void cross(double(*callback)(double x))
{
    int i, j;
    int mask1, mask2;

    for (i = 0; i < SUM; i++)
    {
        gen_new[i].crossflag = 0;
    }

    for (i = 0 ; i < SUM ; i++)
    {
        j = randbit(0, SUM - 1, i);

        if (randsign(crossp) == 1)      //按照crossp的概率对选择的染色体进行交叉操作
        {
            mask1 = createmask(randbit(0, 14));         //由ranbit选择交叉位
            mask2 = ~mask1;             //形成一个类似000111之类的二进制码编码
            gen_new[i].info = ((gen_group[i].info) & mask2) + ((gen_group[j].info) & mask1);
            gen_new[i].suitability = callback(convertionB2D(gen_new[i].info));
        }
        else        //不进行交叉
        {
            gen_new[i].info = gen_group[i].info;
            gen_new[i].suitability = gen_group[i].suitability;
        }

        gen_new[i].crossflag = 1;
        gen_new[j].crossflag = 1;
    }
}

void mutation()
{
    int i, j;
    int gentinfo;
    double gentsuitability;
    for (i = 0 ; i < SUM ; i++)
    {
        if (randsign(mp) == 1)                  //按照变异概率进行变异操作
        {
            double x;
            int i, j = randbit(0, 14);          //确定变异多少位
            for (i = 0 ; i < j ; i++)
            {
                int m, j = randbit(0, 14);      //确定变异第几位
                m = 1 << j;
                gen_group[i].info = gen_group[i].info ^ m;
            }
            x = convertionB2D(gen_group[i].info);
            gen_group[i].suitability = TestFunction;
        }
    }
}


void selection()
{
    int i;

    quickSort(gen_group, 0, SUM);
    quickSort(gen_new, 0, SUM);
    for (i = 0; i < SUM; i++)
    {
        if (gen_group[i].suitability > gen_new[i].suitability)
        {
            gen_group[i].info = gen_new[i].info;
            gen_group[i].suitability = gen_new[i].suitability;
        }
    }
}

static inline gen result(void)
{
    return gen_result;
}

int randsign(double p)//按概率p返回1
{
    if (rand() > (p * (RAND_MAX + 1)))
        return 0;
    else return 1;
}

int convertionD2B(double x)
{
    int g;
    g = (x * 1000) + 8000;
    return g;
}

int createmask(int a)
{
    int mask;
    mask = (1 << (a + 1)) - 1;
    return mask;
}

result_t solution(int min, int max, double(*callback)(double x))
{
    result_t ret;

    initiate(min, max, callback);               //产生初始化种群

    int i;
    for (i = 0 ; i < MAXloop ; i++)
    {
        evaluation();   //对种群进行评估、排序
        if (record() == 1)   //满足终止规则1，则flag=1并停止循环
        {
            break;
        }

        cross();            //进行交叉操作
        mutation();         //变异操作
        selection();        //对父子种群中选择最优的NUM个作为新的父种群
    }

    ret.x = convertionB2D(result().info, min);
    ret.y = result().suitability;

    return ret;
}