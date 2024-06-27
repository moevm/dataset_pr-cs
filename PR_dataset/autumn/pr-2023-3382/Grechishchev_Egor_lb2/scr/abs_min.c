#include <stdio.h>
#include <stdlib.h>

int abs_min(int arr[], int size){
    int min = 100000;
    for( int i =0 ; i < size; i++ ){
        if (abs(arr[i]) < abs(min)){
            min = arr[i];
        }
    }
    return min;
}