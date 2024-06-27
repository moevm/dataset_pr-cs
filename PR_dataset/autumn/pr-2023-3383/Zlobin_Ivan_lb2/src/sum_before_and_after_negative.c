#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int arr[]){
       int sum=0,i;
       for(i=0;i<index_first_negative(arr);++i){
               sum+=abs(arr[i]);
       }
       for(i=index_last_negative(arr);i<100;++i){
               sum+=abs(arr[i]);
       }
       return sum;
}

