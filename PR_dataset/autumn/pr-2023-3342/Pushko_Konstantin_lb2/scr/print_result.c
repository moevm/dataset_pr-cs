#include<stdio.h>
#include"print_result.h"
#include"max.h"
#include"min.h"
#include"diff.h"
#include"sum.h"
#define OUTPUT_FROMAT "%d\n"

void print_result(int* arr, int arr_size, int operation_number)
{
    switch (operation_number)
    {
    case 0: printf(OUTPUT_FROMAT, max(arr, arr_size));
        break;
    case 1: printf(OUTPUT_FROMAT, min(arr, arr_size));
        break;
    case 2: printf(OUTPUT_FROMAT, diff(arr, arr_size));
        break;
    case 3: printf(OUTPUT_FROMAT, sum(arr, arr_size));
        break;
    default:printf("%s\n","Данные некорректны");

    }

}