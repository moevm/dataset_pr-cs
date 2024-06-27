#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"

int sum_before_and_after_negative(int arr[100]){
    int sum = 0;
    int first_negative = index_first_negative(arr);
    int last_negative = index_last_negative(arr);
    for (int index = 0; index < first_negative; index++){
        sum += abs(arr[index]);
    }
    for (int index = last_negative; index < 100; index++){
        sum += abs(arr[index]);
    }
    return sum;
}
