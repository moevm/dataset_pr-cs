#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdlib.h>
int sum_between_negative_func(int arr[], int count){
    int sum_between_negative = 0;
    for (int i = index_first_negative_func(arr, count);i<index_last_negative_func(arr, count);i++){
        sum_between_negative+=abs(arr[i]);
    }
    return sum_between_negative;
}
