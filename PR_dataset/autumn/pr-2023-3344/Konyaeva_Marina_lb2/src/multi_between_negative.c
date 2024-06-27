#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[],int n) {
    int mul = 1;
    for (int i = index_first_negative(arr, n); i < index_last_negative(arr,n); i++) {
        mul = mul * arr[i];
    }
    return mul;
}
