#include <stdio.h>
#include <stdlib.h>
#include "index_1.h"

int sum(int arr[] , int size){
    int sam = 0;
    int index_m = index_1(arr, size);
    for( int i = index_m; i<size; i++){
        sam +=arr[i];
    }
    return sam;
}