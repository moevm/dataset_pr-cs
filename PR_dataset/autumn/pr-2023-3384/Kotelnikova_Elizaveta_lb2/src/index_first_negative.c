#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
int index_first_negative(int i, int arr[100]){
    int j = 0;
    for (j; j<i; ++j){
        if (arr[j]<0){
            return j;
        }
    }
 }