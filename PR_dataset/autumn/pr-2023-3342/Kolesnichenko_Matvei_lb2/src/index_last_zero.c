#include <stdio.h>

int index_last_zero(int arr[], int len_arr){
    for (int i = len_arr - 1; i >= 0; --i){
        if (arr[i] == 0){
            return i;
        }
    }
    return -1;
}