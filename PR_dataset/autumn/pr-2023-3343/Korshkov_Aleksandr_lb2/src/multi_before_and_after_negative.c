#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

void multi_before_and_after_negative(int arr[20], int finish2) {
    int k = 1, finish1 = index_first_negative(arr, 0),
    start2 = index_last_negative(arr, 0); 

    for (int start = 0; start < finish1; start++) {
        k *= arr[start];
    }
    for (start2; start2 < finish2; start2++) {
        k *= arr[start2];
    }

    printf("%d", k);
}