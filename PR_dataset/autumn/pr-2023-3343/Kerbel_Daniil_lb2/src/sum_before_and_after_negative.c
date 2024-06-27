#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_before_and_after_negative(int arr[], int n) {

    int first_negative_index = index_first_negative(arr, n);

    int last_negative_index = index_last_negative(arr, n);

    int summa = 0;

    for (int i=0; i < first_negative_index; i++){

        summa += abs(arr[i]);

    }
    for (int i = last_negative_index; i < n; i++){

        summa += abs(arr[i]);

    }

    return summa;
}
