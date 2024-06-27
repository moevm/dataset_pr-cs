#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int size) {
    int i1, i2, answer = 1;
    i1 = index_first_negative(arr, size);
    i2 = index_last_negative(arr, size);
    for (int i = 0; i < i1; i++) {
        answer *= arr[i];
    }
    for (int i = i2; i < size; i++) {
        answer *= arr[i];
    }
    return answer;
}