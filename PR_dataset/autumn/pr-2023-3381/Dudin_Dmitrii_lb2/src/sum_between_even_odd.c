#include <stdio.h>
#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int arr[],int k) {
    int f = index_first_even(arr,k), l = index_last_odd(arr,k);
    int s = 0;
    for (int i = f; i < l; i++) {
        s += abs(arr[i]);
    }
    return s;
}
