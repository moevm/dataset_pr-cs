#include <stdio.h>
#include <stdlib.h>
#include "sum_abs.h"

int sum_abs(int arr[], int start, int finish){
    int sum = 0;
    for(int k = start; k <= finish; k++){
        sum += abs(arr[k]);
    }
    return sum;
}