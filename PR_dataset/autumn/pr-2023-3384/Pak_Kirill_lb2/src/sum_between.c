#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"


int sum_between(int arr[],int first_zero,int last_zero){
    int sum=0;
    for(int i=first_zero;i<last_zero;i++){
        sum=sum+abs(arr[i]);
    }
    return sum;
}