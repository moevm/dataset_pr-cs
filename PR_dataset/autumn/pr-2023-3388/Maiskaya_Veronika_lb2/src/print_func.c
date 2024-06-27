#include "print_func.h"

void print_func(int func_value, int arr[N], int index){
    switch (func_value){
    case 0:
        printf("%d", index_first_even(arr, index));
        break;
    case 1:
        printf("%d", index_last_odd(arr, index));
        break;
    case 2:
        printf("%d", sum_between_even_odd(arr, index));
        break;
    case 3:
        printf("%d", sum_before_even_and_after_odd(arr, index));
        break;
    default:
        printf("Данные некорректны");
    }
}
