#include "max.h"
#include "min.h"
int diff(int arr[], int size) {
    int maximum = max(arr, size);
    int minimum = min(arr, size);
    if (minimum < 0){
        return maximum + minimum;
    }else{
        return maximum - minimum;
    }
}