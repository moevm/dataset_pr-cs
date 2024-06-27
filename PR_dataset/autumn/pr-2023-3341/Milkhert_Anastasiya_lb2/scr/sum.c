#include "sum.h"
#include "abs_max.h"

int sum(int arr[], int arr_elements_count) {
    int sum = 0;
    int max = abs_max(arr, arr_elements_count);

    int flag = 0;
    for (int j = 0; j < arr_elements_count; j++) {
        if (arr[j] == max) {
            sum += arr[j];
            flag = 1;
        } else if (flag == 1) {
            sum += arr[j];
        }
    }
    return sum;
}