#include <stdio.h>
#include "min.h"

int min(int* arr, int len){
 
    int min = 100000;
    for (int i = 0; i < len; i++){

        if (min > arr[i]){
                
            min = arr[i];
        }
    }
    return min;
}
