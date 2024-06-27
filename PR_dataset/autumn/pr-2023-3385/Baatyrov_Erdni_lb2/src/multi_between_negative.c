#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdio.h>

void multi_between_negative(int arr[], int n) {
    int first = index_first_negative(arr, n);
    int last = index_last_negative(arr, n);
    long long int multi = 1;
    for (int i = first; i < last; ++i) {
        multi *= arr[i];
    }
    printf("%lld\n", multi);
    return;
}

