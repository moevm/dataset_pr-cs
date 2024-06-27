#include <stdio.h>
#include "input_arr.h"

void input_arr(int *arr, int *n)
{
 while (getchar() != '\n')
    {
        scanf("%d", &arr[(*n)++]);
    }
}

