#include "max.h"

int max(int *arr, int arr_size){
        int result = arr[0];
        for (int i = 1; i < arr_size; i++){
                if (arr[i] >= result)
                {
                        result = arr[i];
                }
        }
        return result;
}

