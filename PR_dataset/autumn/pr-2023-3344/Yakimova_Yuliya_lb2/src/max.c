#include "max.h"

int getMax(int arr[], int length) {
    int max = 0;
    for (int i = 0; i < length; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}