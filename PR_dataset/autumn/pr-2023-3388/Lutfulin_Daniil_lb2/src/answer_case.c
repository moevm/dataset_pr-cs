#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#include "get_answer.h"

#ifndef ERROR
#define ERROR "Данные некорректны\n"
#endif


void answer_case(int case_num, int *arr, int arr_len){
    switch(case_num){
        case 0:
                get_answer(index_first_negative(arr, arr_len));
                break;
            case 1 :
                get_answer(index_last_negative(arr, arr_len));
                break;
            case 2:
                get_answer(sum_between_negative(arr, arr_len));
                break;
            case 3:
                get_answer(sum_before_and_after_negative(arr, arr_len));
                break;
            default:
                get_answer(-1);
                break;
    }
}
