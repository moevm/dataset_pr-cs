#include "max.h"

int max(int arr[], int size) {
    int max_element = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_element) {
            max_element = arr[i];
        }
    }
    return max_element;
}
