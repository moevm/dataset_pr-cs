#include <stdio.h>
#include "data_reading.h"
#include "choice_answer.h"

int main(){
    int *input_data;
    input_data = data_reading();
    int len_arr = input_data[0];
    int func_num = input_data[1];
    int arr[len_arr];
    for (int k=2; k <len_arr+2; k++){ 
        arr[k-2] = input_data[k];
    }
    choice_answer(arr, len_arr, func_num);
    return 0;
}
