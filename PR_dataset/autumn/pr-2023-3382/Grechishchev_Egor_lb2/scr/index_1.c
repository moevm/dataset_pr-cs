#include <stdio.h>
#include <stdlib.h>

int index_1(int arr[], int size){
    int index_max = 0;
    int max = 0;
    for( int i = 0 ; i < size ; i++){
        if (abs(arr[i]) > abs(max)){
            index_max = i ;
            max = arr[i]; 
        }
    }
    return index_max;
}