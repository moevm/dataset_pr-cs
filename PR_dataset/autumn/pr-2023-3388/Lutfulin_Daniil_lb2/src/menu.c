#include <stdio.h>
#include <stdlib.h>
#include "get_numbers.h"
#include "answer_case.h"

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif

int main(){
    int case_num, arr_len;
    int *arr;
    get_numbers(&arr_len, &case_num, &arr);
    answer_case(case_num, arr, arr_len);
    free(arr);
    return 0;
}
