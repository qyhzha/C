#include <stdio.h>

int InversePairs(int array[], int length)
{
    int ret = 0;

    for (int i = 1; i < length; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[j] > array[i])
            {
                ret++;
            }
        }
    }

    return ret;
}

int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7, 0};

    int size = InversePairs(array, sizeof(array) / sizeof(int));

    printf("size(%d).", size);

    return 0;
}
