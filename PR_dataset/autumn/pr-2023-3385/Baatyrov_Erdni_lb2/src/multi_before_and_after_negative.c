#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdio.h>

void multi_before_and_after_negative(int arr[], int n) {
    int first = index_first_negative(arr, n);
    int last = index_last_negative(arr, n);
    long long int multi = 1;
    for (int i = 0; i < first; ++i) {
        multi *= arr[i];
    }
    for (int i = last; i < n; ++i) {
        multi *= arr[i];
    }
    printf("%lld\n", multi);
    return;
}
