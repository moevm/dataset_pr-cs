#include <stdlib.h>
#include "sum_between.h"

int sum_before_and_after(int arr[], int len)
{
    int sum = 0;
    for(int i = 0; i < len; i++){
        sum += abs(arr[i]);
    }
    return sum - sum_between(arr, len);
}
