#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

int output(int sign, int numbers[], int size){

    switch(sign){

        case 0:
            printf(print_str,index_first_negative(numbers, size));
            break;

        case 1:
            printf(print_str,index_last_negative(numbers, size));
            break;

        case 2:
            printf(print_str,sum_between_negative(numbers, size));
            break;

        case 3:
            printf(print_str,sum_before_and_after_negative(numbers, size));
            break;

        default:
            printf("%s\n","Данные некорректны");
    }
}
