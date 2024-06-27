#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

void multi_between_negative(int arr[20]) {
    int k = 1, start = index_first_negative(arr, 0), 
    finish = index_last_negative(arr, 0);

    for (start;start < finish;start++) {
        k *= arr[start];
    }

    printf("%d", k);
}