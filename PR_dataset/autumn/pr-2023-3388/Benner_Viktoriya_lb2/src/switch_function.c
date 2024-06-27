#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "switch_function.h"
#define ERROR_MESSAGE "Данные некорректны"
void switch_function(int type, int arr[], int size){
    switch (type){
    case 0:
        printf("%d", index_first_even(arr,size));
        break;
    case 1:
        printf("%d", index_last_odd(arr,size));
        break;
    case 2:
        printf("%d", sum_between_even_odd(arr,size));
        break;
    case 3:
        printf("%d", sum_before_even_and_after_odd(arr,size));
        break;
    default:
        printf("%s\n", ERROR_MESSAGE);
        break;
    }
    return 0;
}
