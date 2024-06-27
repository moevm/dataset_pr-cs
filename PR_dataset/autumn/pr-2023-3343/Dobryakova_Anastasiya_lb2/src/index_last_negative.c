#include <stdio.h>
#include <stdlib.h>

int index_last_negative(int arr[], int size){
    for(int i=size-1;i>=0;i--){
        if(arr[i]<0){
            return i;
            break;
        }
    }
}
