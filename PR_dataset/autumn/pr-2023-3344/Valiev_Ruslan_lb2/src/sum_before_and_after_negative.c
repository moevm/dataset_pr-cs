#include <stdlib.h>
int sum_before_and_after_negative(int* arr, int N) {
    int end1 = index_first_negative(arr, N);
    int start2 = index_last_negative(arr, N);
    if (end1 == -1) return -1;
    int sum = 0;
    for (int i = 0; i < end1; i++) sum += abs(arr[i]);
    for (int i = start2; i < N; i++) sum += abs(arr[i]);
    return sum;
}

