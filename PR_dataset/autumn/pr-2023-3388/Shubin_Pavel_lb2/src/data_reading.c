#include <stdio.h>
#include "data_reading.h"

#define LEN_ARRAY 100
#define LEN_ANSWER_ARRAY 102

int* data_reading(){
    int arr[LEN_ARRAY];
    static int answer_array[LEN_ANSWER_ARRAY]; 
    int k = 0, len_arr = 0, func_num = -1;
    do {
        scanf("%d", &arr[k]);
        len_arr++;
        k++;
    }while(getchar() != '\n');

    answer_array[0] = len_arr - 1; 
    for(k = 1; k <= len_arr; k++){
        answer_array[k] = arr[k-1];
    }
    return answer_array;
}
