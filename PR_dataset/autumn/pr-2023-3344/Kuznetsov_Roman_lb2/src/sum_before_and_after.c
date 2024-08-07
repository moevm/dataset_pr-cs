#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int arr[], int size) {
    int first_zero_index = index_first_zero(arr, size);
    int last_zero_index = index_last_zero(arr, size);
    
    int sum = 0;
    for (int i=0; i<first_zero_index; i++) {
        sum += abs(arr[i]);
    }

    for (int i=last_zero_index + 1; i<size; i++) {
        sum+= abs(arr[i]);
    }

    return sum;
}
