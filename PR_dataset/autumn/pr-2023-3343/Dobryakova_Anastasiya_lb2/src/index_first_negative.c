#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int arr[], int size){
    for(int i=0;i<size;i++){
        if(arr[i]<0){
            return i;
            break;
        }
    }
}
