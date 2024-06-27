#include<stdio.h>
#include"input_data.h"
void input_data(int* arr, int* arr_size, int* operation_number)
{
    scanf("%d", operation_number);
    while (getchar() != '\n')
    {
        scanf("%d", &arr[(*arr_size)++]);
    }
    
}
