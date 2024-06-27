#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"

int sum_between_negative(int arr[100]){
    int sum = 0;
    int first_negative = index_first_negative(arr);
    int last_negative = index_last_negative(arr);
    for (int index = first_negative; index < last_negative; index++){
        sum += abs(arr[index]);
    }
    return sum;
}
