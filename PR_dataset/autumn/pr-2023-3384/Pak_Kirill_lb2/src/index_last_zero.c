#include <stdio.h>
#include <stdlib.h>
#include "index_last_zero.h"

int index_last_zero(int arr[],int len){
    for(int i=len;i>0;i--){
        if(arr[i-1]==0){
            return i-1;
            break;
        }
    }
    return 0;
}