#include "abs_max.h"
#include "abs_min.h"
int diff(int arr[], int arr_size){
        return abs_max(arr_size, arr[]) - abs_min(arr_size, arr[]);
}