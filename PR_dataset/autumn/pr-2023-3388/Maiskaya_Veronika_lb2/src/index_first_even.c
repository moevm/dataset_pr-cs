#include "index_first_even.h"

int index_first_even(int arr[N], int arr_length){
    int index = -1;
    for (int i = 0; i <= arr_length; i++){
        if (abs(arr[i] % 2) == 0){
            index = i;
            break;
        }
    }
    return index;
}
