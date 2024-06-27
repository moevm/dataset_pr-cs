#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"

int sum_before_and_after(int arr[],int first_zero,int last_zero,int len){
    return sum_between(arr,0,len)-sum_between(arr,first_zero,last_zero);
}
