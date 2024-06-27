#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"

int sum(int arr[], int len){
    int x = abs_max(arr, len);
    int sum = 0, f = 0;
    for(int i = 0; i < len; i++){
        if (f == 0 && arr[i] == x){
            f = 1;
        }
        if (f == 1){
            sum += arr[i];
        }
    }
    return sum;
}  
