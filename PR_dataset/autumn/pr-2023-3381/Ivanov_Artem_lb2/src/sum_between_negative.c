#include <stdlib.h>

#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

//функция для значения 2
int sum_between_negative(int arr[], int len) {
        int sum = 0;
        for (int i = index_first_negative(arr, len); i < index_last_negative(arr, len); i++) {
                sum = sum + abs(arr[i]);
        }
        return sum;
} 
