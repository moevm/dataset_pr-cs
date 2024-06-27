#include “abs_max.h”
#include “abs_min.h”
int diff(int arr[], int arrsize){
    int df = abs_max(arr, arrsize, 1) - abs_min(arr, arrsize);
    return df;
}