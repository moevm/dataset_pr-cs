#include <stdlib.h>
#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int arr[], int len){
    
    int i_first = index_first_even(arr, len);
    int i_last = index_last_odd(arr, len);
    int sum = 0;
    for(int i=i_first; i<i_last; i++){
        sum += abs(arr[i]);
    }
    return(sum);
}

