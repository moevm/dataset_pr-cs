#include "sum.h"
#include "min.h"

int sum(int arr[], int arr_len)
{
    int res_sum = 0, i;
    int min_element = min(arr, arr_len);
    
    for (i = 0; i < arr_len; i++){
        if (arr[i] == min_element){
            break;
        }
        res_sum += arr[i];
    }
    return res_sum;
}
