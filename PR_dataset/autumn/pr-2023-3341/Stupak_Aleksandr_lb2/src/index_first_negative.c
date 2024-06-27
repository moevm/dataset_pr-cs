#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int arr[], int i) {
    for (int k = 0; k < i; k++) {
        if (arr[k] < 0) {
            return k;
        }
    }
}