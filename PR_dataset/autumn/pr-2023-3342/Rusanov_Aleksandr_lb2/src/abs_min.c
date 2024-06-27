#include "abs_min.h"

int abs_min(int arr[], int size){
    int result = arr[0];
    for (int i = 1; i < size; i++){
        if ((abs(arr[i])) < (abs(result))){
            result = arr[i];
        }
    }
    return result;
}