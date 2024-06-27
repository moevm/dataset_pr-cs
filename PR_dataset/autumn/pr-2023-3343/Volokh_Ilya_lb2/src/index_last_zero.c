#include "index_last_zero.h"
#include <stdio.h>
#include <stdlib.h>
int index_last_zero(int arr[], int size_now){
    int last = -1;
    for(int k = size_now - 1; k >= 0 ; k--)
        if(arr[k] == 0){
            last = k;
            break;
        }
    return last;
}
