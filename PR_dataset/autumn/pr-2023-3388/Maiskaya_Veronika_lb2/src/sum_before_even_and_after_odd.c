#include "sum_before_even_and_after_odd.h"

int sum_before_even_and_after_odd(int arr[N], int arr_length){
    int sum = 0;

    for (int i = 0; i < index_first_even(arr, arr_length); i++){
        sum += abs(arr[i]);
    }
    for (int i = index_last_odd(arr, arr_length); i < arr_length; i++){
        sum += abs(arr[i]);
    }
    return sum;
}
