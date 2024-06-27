#include "sum.h"
#include "abs_max.h"

int sum(int arr[], int size) {
        int max = abs_max(arr, size);
        int sum_num = 0;
        for (int i = 0; i < size; i++) {
                if (arr[i] == max) {
                        for (int j = i; j < size; j++) {
                                sum_num += arr[j];
                        }
                        break;
                }
        }
        return sum_num;
}

