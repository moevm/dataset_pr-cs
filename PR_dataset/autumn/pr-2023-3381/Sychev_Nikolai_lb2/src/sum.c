#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"

int sum(int arr[], int len_arr){
    int abs_maxim = abs_max(arr,len_arr);
    int sum = 0,flag = 0;
    for (int i = 0;i < len_arr; i++){
        if (flag == 0 && arr[i] == abs_maxim){
            flag = 1;
        }
        if (flag == 1){
            sum += arr[i];
        }
    }
    return sum;
}
