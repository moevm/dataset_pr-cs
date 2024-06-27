#include "sum.h"

int sum(int arr[], int size) {
    int min_element = min(arr, size);
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == min_element) {
            break;
        }
        sum += arr[i];
    }
    return sum;
}
