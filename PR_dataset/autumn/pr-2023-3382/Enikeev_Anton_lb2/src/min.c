#include "min.h"
#include <limits.h>

int min(int arr[], int arr_len)
{
    int min_res = INT_MAX, i;
    for (i = 0; i < arr_len; i++){
        if (arr[i] < min_res){
            min_res = arr[i];
            }
    }
    return min_res;
}
