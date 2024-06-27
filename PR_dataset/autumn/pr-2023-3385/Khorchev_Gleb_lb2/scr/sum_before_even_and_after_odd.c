#include <stdlib.h>
#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int arr[], int len){
    
    int i_first = index_first_even(arr, len);
    int i_last = index_last_odd(arr, len);
    int sum = 0;
    for(int i=0; i<i_first; i++){
        sum += abs(arr[i]);
    }
    for(int i=i_last; i<len; i++){
        sum += abs(arr[i]);
    }
    return(sum);
    
}
