#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int len) {
    int first_negative = index_first_negative(arr, len);
    int last_negative = index_last_negative(arr, len);
    int product = 1;
    for (int i = 0; i < first_negative; i++) {
        product *= arr[i];
    }
    for (int i = last_negative; i < len; i++) {
        product *= arr[i];
    }
    return product;
}