#include "index_last_odd.h"

int index_last_odd(int arr[N], int arr_length){
    int index = -1;
    for (int i = arr_length-1; i >= 0; i--){
        if (abs(arr[i]) % 2 == 1){
            index = i;
            break;
        }
    }
    return index;
}
