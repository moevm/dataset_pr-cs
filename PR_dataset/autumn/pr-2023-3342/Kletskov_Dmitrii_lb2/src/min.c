#include "min.h"

int min(int arr[], int size) {
    int min_element = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_element) {
            min_element = arr[i];
        }
    }
    return min_element;
}
