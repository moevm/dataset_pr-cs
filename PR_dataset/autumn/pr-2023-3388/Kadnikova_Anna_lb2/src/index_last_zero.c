#include <stdio.h>
#include <stdlib.h>
#include "index_last_zero.h"
#define ERR -1
int index_last_zero(int arr[], int len_arr){
    int index = ERR;
    for (int j = len_arr; j > 0; j--){
        if (arr[j-1] == 0){
            index = j-1;
            break;
        }
    }
    return index;
}