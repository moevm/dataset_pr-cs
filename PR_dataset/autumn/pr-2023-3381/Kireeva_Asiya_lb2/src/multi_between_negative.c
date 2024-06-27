#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[], int size) {
    int i1, i2, answer = 1;
    i1 = index_first_negative(arr, size);
    i2 = index_last_negative(arr, size);
    for (int i = i1; i < i2; i++) {
        answer *= arr[i];
    }
    return answer;
}