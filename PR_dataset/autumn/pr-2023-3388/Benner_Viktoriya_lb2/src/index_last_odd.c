#include <stdio.h>
#include "index_last_odd.h"

int index_last_odd(int arr[], int size){
    for (int i = size - 1; i >= 0; i--)
        if (arr[i] % 2 != 0)
            return i;
}