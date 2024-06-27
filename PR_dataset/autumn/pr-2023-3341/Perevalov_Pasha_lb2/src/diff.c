#include "max.h"
#include "min.h"
int diff(int arr[], int size) {
    return max(arr, size) - min(arr, size);
}