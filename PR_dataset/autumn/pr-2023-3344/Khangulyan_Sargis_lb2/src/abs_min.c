#include <stdlib.h>
int abs_min(int arr[], int arrsize){
    int min = arr[0]; 
    int i;
    for (i = 0; i < arrsize; i++){
        if (abs(arr[i]) < abs(min)){
            min = arr[i];
        }
    }
    return min;
}