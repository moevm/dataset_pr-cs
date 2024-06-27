#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"

int sum_before_and_after_negative(int arr[], int arr_len) {
    int first = index_first_negative(arr, arr_len), last = index_last_negative(arr,arr_len);
    int summary = -1;
    if (first != -1){
        summary++;
        for (int i = 0; i < first; i++) {
            summary += abs(arr[i]);
    }
    for (int i = last; i < arr_len; i++) {
        summary += abs(arr[i]);
    }}
    return summary;
}
