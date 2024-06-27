#include “abs_max.h”
int sum(int arr[], int arrsize){
    int sum = 0;
    int i;
    for (i = abs_max(arr, arrsize, 0); i < arrsize; i++){
        sum += arr[i];
    }
    return sum;
}