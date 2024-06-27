#include <stdio.h>
#include <stdlib.h>
#include "index_last_negative.h"
int index_last_negative(int i, int arr[100]){
    int k=i-1;
    for (i-1; k>=0; --k){
        if (arr[k]<0){
            return k;
        }
    }
}