#include <stdlib.h>
#include <stdio.h>
#include "abs_min.h"
#include "abs_max.h"

int diff(int arr[],int len_arr){
    return abs_max(arr,len_arr) - abs_min(arr,len_arr);
}
