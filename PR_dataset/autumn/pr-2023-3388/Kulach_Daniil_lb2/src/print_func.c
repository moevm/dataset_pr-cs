#include "print_func.h"
#define FORMAT_STRING "%d\n"
void print_func(int func_value, int arr[N], int index){
    switch (func_value){
    case 0:
        printf(FORMAT_STRING, index_first_even(arr, index));
        break;
    case 1:
        printf(FORMAT_STRING, index_last_odd(arr, index));
        break;
    case 2:
        printf(FORMAT_STRING, sum_between_even_odd(arr, index));
        break;
    case 3:
        printf(FORMAT_STRING, sum_before_even_and_after_odd(arr, index));
        break;
    default:
        printf("Данные некорректны\n");
    }
}
