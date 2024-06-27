#include "sum.h"

int get_sum(int min,int array[])
{
    int i = 0;
    int sum = 0;
    while(array[i] != min)
    {
        sum+=array[i];
        i++;
    }
    return sum;
}
