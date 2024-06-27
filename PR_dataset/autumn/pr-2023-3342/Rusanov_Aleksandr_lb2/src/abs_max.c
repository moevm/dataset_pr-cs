#include "abs_max.h"

int abs_max(int arr[], int size, int flag){
    int result = arr[0];
    int index = 0;
    for (int i = 1; i < size; i++){
        if (abs(arr[i]) > (abs(result))){
            result = arr[i];
            index = i;
        }
    }
    if (flag == 1){
        return result;
    }
    return index;

}