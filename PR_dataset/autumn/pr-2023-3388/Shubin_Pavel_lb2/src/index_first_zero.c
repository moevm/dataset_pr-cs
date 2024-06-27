#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"

int index_first_zero(int arr[], int len_arr){
    for(int i=0; i < len_arr; i++){
        if(arr[i]==0){
            return i;
        }
    }
    return -1;
}