#include <stdio.h>
#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int arr[], int n) {

    int first_negative_index = index_first_negative(arr, n);

    int last_negative_index = index_last_negative(arr, n);

    int summa = 0;

    for(int i = first_negative_index; i < last_negative_index; i++){

        summa += abs(arr[i]);

    }

    return summa;

}
