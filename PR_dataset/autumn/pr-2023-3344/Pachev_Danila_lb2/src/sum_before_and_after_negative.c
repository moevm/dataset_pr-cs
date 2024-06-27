#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdlib.h>
int sum_before_and_after_negative_func(int arr[], int count){
    int sum_before_and_after_negative = 0;
    for (int i = 0;i<index_first_negative_func(arr, count);i++){
        sum_before_and_after_negative+=abs(arr[i]);
    }
    for (int i = index_last_negative_func(arr, count);i<=count;i++){
        sum_before_and_after_negative+=abs(arr[i]);
    }
    return sum_before_and_after_negative;
    
    
}
