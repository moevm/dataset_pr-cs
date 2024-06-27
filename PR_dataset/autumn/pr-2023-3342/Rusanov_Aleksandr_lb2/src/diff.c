#include "diff.h"
int diff(int arr[], int size){
    return abs_max(arr, size, 1) - abs_min(arr, size);
}
