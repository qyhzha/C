#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Parameters:
//        numbers:     an array of integers
//        length:      the length of array numbers
//        duplication: (Output) the duplicated number in the array number
// Return value:       true if the input is valid, otherwise false
bool duplicate(const int numbers[], int length, int* duplication)
{
    int ret = false;
    //在这道题中，不适合考虑内存申请失败的情况
    char *array = (char *)malloc(length);

    memset(array, 0, length);

    for(int i = 0; i < length && !ret; i++)
    {
        array[numbers[i]]++;

        if (array[numbers[i]] >= 2)
        {
            *duplication = numbers[i];
            ret = true;
        }
    }

    return ret;
}

int main()
{
    int array[5] = {2, 4, 2, 1, 4};
    int a;

    bool result = duplicate(array, 5, &a);

    printf("result(%d), duplication(%d)", result, a);

    return 0;
}
