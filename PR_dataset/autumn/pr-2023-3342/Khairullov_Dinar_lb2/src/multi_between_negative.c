#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[], int num_of_arr_elements){
    int last_neg = index_last_negative(arr, num_of_arr_elements);
    int first_neg = index_first_negative(arr, num_of_arr_elements);
    int res = 1;
    for(int i = first_neg; i<last_neg; i++){
        res = res*arr[i];
    }
    return res;
}