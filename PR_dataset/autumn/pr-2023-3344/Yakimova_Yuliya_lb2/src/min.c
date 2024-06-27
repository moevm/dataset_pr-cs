#include "min.h"

int getMin(int arr[], int length) {
    int min = 100;
    for (int i = 0; i < length; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    return (min);
}