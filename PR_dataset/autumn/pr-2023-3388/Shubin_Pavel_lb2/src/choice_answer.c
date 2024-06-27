#include <stdio.h>
#include "choice_answer.h"
#include "output_answer.h"

void choice_answer(int arr[], int len_arr, int func_num){
    switch(func_num){
        case 0:
                output_answer(index_first_zero(arr, len_arr));
                break;
        case 1:
                output_answer(index_last_zero(arr, len_arr));
                break;
        case 2:
                output_answer(sum_between(arr, len_arr));
                break;
        case 3:
                output_answer(sum_before_and_after(arr, len_arr));
                break;
        default:
                output_answer(-1);
    }
}