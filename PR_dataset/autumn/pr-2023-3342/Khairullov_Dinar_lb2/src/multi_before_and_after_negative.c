#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int num_of_arr_elements){
    int first_neg = index_first_negative(arr, num_of_arr_elements);
    int last_neg = index_last_negative(arr, num_of_arr_elements);
    int res = 1;
    for(int i = 0; i<first_neg; i++){
        res=res*arr[i];
    }
    for(int i = last_neg; i <num_of_arr_elements; i++){
        res=res*arr[i];
    }
    return res;
}