#include "max.h"
#include <limits.h>

int max(int arr[], int arr_len)
{
    int max_res = INT_MIN, i;
    for (i = 0; i < arr_len; i++){
        if (arr[i] > max_res){
            max_res = arr[i];
        }
    }
    return max_res;
}
