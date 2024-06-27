#include <stdlib.h>

#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

//функция для значения 3
int sum_before_and_after_negative(int arr[], int len) {
        int sum = 0;
        for (int i = 0; i < index_first_negative(arr, len); i++) {
                sum = sum + abs(arr[i]);
        }
        for (int i = index_last_negative(arr, len); i < len; i++) {
                sum = sum + abs(arr[i]);
        }
        return sum;
}

