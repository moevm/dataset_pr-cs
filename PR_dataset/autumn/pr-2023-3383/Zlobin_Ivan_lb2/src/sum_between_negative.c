#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_between_negative(int arr[]){
        int sum=0;
        for(int i=index_first_negative(arr);i<index_last_negative(arr);++i){
                sum+=abs(arr[i]);
        }
        return sum;
}

