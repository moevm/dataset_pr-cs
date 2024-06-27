#include "index_last_negative.h"

int index_last_negative(int arr[], int arr_size){
    for (int j = arr_size-1; j >= 0; j--){
        if (arr[j] < 0){
            return j;
        }
    }
}

