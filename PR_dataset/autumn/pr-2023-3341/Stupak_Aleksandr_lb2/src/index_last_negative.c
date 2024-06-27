#include <stdio.h>
#include <stdlib.h>

int index_last_negative(int arr[], int i) {
    for(int k = i - 1; k >= 0; k--) {
        if(arr[k] < 0){
            return k;
        }
    }
}