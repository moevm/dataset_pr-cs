#include "sum_between_even_odd.h"

int sum_between_even_odd(int arr[N], int arr_length){
    int sum = 0;
    for (int i = index_first_even(arr, arr_length); i < index_last_odd(arr, arr_length); i++){
        sum += abs(arr[i]);
    }
    return sum;
}
