#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative (int arr[], int size) {
    int multi = 1;
    for (int i = index_first_negative(arr, size); i < index_last_negative(arr, size); i++)
        multi *= arr[i];
    return multi;
}