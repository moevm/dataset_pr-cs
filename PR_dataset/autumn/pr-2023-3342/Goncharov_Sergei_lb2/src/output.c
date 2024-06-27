#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "output.h"
#define FORMAT "%d\n"

void output(int operation_number, int array[], int array_size){
    switch(operation_number){
        case 0:
            printf(FORMAT, index_first_even(array, array_size));
            break;
        case 1:
            printf(FORMAT, index_last_odd(array, array_size));
            break;
        case 2:
            printf(FORMAT, sum_between_even_odd(array, array_size));
            break;
        case 3:
            printf(FORMAT, sum_before_even_and_after_odd(array, array_size));
            break;
        default:
            printf("Данные некорректны\n");
    }
}
