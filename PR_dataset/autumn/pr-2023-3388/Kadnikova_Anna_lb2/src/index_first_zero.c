#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#define ERR -1

int index_first_zero(int arr[], int len_arr){
    int index = ERR;
    for (int j = 0; j < len_arr; j++){
        if (arr[j] == 0){
            index = j;
            break;
        }
    }
    return index;
}