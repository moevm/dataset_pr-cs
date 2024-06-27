#include "sum_before_even_and_after_odd.h"
int sum_before_even_and_after_odd(int arr[], int array_length){
    int sum = 0;
    for(int i = index_last_odd(arr,array_length); i < array_length;++i){
        sum += abs(arr[i]);
    }
    for(int i = 0 ; i < index_first_even(arr,array_length); ++i){
        sum += abs(arr[i]);
    }

    return sum;
}
