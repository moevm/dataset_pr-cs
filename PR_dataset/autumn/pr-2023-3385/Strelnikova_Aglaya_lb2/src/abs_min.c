#include <stdio.h>
#include <stdlib.h>

int abs_min(int arr[], int len){
    int a = arr[0];
    int min = abs(arr[0]);
    for(int i = 1; i < len; i++){
        if(abs(arr[i]) < min){
            min = abs(arr[i]);
            a = arr[i];
        }
    }
    return a;
}

