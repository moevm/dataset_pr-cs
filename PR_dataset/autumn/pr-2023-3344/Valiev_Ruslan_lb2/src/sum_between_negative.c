#include <stdlib.h>
int sum_between_negative(int* arr, int N) {
    int start = index_first_negative(arr, N);
    int end = index_last_negative(arr, N);
    if (start == -1) return -1;
    int sum = 0;
    for (int i = start; i < end; i++) sum += abs(arr[i]);
    return sum;
}

