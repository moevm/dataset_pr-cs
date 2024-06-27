#include<stdio.h>
#include "input_array_data.h"

void input_array_data(int *array, int *length)
{
    while(scanf("%d", array)==1)
    {
        *length+=1;
        array++;
    }
}
