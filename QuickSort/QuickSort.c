#include <stdio.h>

typedef int DataType;

static void QuickSort(DataType *data, int low, int high)
{
    int i = low, j = high;
    DataType temp = data[low];  //取第一个元素为标准数据元素

    while (i < j)
    {
        while ((i < j) && (temp <= data[j]))
        {
            j--; //在数组的右端扫描
        }

        if (i < j)
        {
            data[i] = data[j];
            i++;
        }

        while ((i < j) && (data[i] <= temp))
        {
            i++; //在数组的左端扫描
        }

        if (i < j)
        {
            data[j] = data[i];
            j--;
        }
    }

    data[i] = temp;

    if (low < i) QuickSort(data, low, i - 1); //对左端子集合进行递归
    if (i < high) QuickSort(data, i + 1, high); //对右端子集合进行递归
}

int main()
{
    int data[10] = {12, 10, 5, 6, 7, 3, 23, 52, 17, 32};
    int i;

    QuickSort(data, 0, 9);

    for (i = 0; i < 10; i++)
    {
        printf("data[%d] = %d\n", i, data[i]);
    }
}
