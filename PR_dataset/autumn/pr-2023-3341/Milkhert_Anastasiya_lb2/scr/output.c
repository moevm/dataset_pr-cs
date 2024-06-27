#include <stdio.h>

#include "output.h"
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

#define N 100
#define func_output "%d\n"

void output(int *key, int arr[N], int *arr_elements_count) {
    switch (*key) {
        case 0:
            printf("func_output", abs_max(arr, *arr_elements_count));
            break;
        case 1:
            printf("func_output", abs_min(arr, *arr_elements_count));
            break;
        case 2:
            printf("func_output", diff(arr, *arr_elements_count));
            break;
        case 3:
            printf("func_output", sum(arr, *arr_elements_count));
            break;
        default:
            printf("Данные некорректны\n");
    }

}