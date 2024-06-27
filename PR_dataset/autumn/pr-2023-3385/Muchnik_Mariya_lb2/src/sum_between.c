#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_between(int arr[], int len)
{
    int sum = 0;
    int a = index_first_zero(arr, len), b = index_last_zero(arr, len);
    for(int i = a+1; i < b; i++){
        sum += abs(arr[i]);
    }
    return sum;
}
