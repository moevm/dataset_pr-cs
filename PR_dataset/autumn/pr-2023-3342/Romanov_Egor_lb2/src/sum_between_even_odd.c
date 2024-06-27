#include "sum_between_even_odd.h"
int sum_between_even_odd(int arr[], int array_length) {
    int sum = 0;
    int first_index = index_first_even(arr,array_length);
    int last_index = index_last_odd(arr,array_length);
    for (int i = first_index; i < last_index; i++) {
        sum += abs(arr[i]);
    }
    return sum;
}
