#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"

int index_first_zero(int quantity, int arr_end[100]){
    for (int k = 0; k < quantity; ++k){
        if (arr_end[k] == 0){
            return k;
        }
    }
}