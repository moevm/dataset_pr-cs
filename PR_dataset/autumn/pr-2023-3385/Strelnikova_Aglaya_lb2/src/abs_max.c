#include <stdio.h>
#include <stdlib.h>
int abs_max(int arr[], int len){
    int a = 0, max = 0;
    for(int i = 0; i < len; i++){
        if(abs(arr[i]) > max){
            max = abs(arr[i]);
            a = arr[i];
        }
    }
    return a;
}

