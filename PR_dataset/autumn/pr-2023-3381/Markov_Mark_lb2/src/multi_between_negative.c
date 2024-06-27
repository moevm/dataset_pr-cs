#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[], int len) {
    int first_negative = index_first_negative(arr, len);
    int last_negative = index_last_negative(arr, len);
    int product = 1;
    for (int i = first_negative; i < last_negative; i++) {
        product *= arr[i];
    }
    return product;
}