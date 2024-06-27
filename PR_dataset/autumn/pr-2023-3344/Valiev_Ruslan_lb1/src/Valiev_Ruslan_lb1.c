#include <stdio.h>
#include <stdlib.h>

int get_index(int begin, int finish, int increment, int* arr) {
    for (int i = begin; i > finish; i -= increment) {
        if (arr[abs(i)] < 0) return abs(i);
    }
    return -1;
}

int index_first_negative(int* arr, int N) {
    return get_index(0, -N, 1, arr);
}

int index_last_negative(int* arr, int N) {
    return get_index(N - 1, -1, 1, arr);
}

int sum_between_negative(int* arr, int N) {
    int start = index_first_negative(arr, N);
    int end = index_last_negative(arr, N);
    if (start == -1) return -1;
    int sum = 0;
    for (int i = start; i < end; i++) sum += abs(arr[i]);
    return sum;
}

int sum_before_and_after_negative(int* arr, int N) {
    int end1 = index_first_negative(arr, N);
    int start2 = index_last_negative(arr, N);
    if (end1 == -1) return -1;
    int sum = 0;
    for (int i = 0; i < end1; i++) sum += abs(arr[i]);
    for (int i = start2; i < N; i++) sum += abs(arr[i]);
    return sum;
}

int main() {
    int type, N;
    int arr[100];
    char c;
    scanf("%d%c", &type, &c);
    int i = 0;
    while (c != '\n') {
        scanf("%d%c", &arr[i], &c);
        i++;
    }
    N = i;
    int res = -1;
    switch (type) {
        case 0:
            res = index_first_negative(arr, N);
            break;
        case 1:
            res = index_last_negative(arr, N);
            break;
        case 2:
            res = sum_between_negative(arr, N);
            break;
        case 3:
            res = sum_before_and_after_negative(arr, N);
            break;
        default:
            printf("Данные некорректны\n");
            return 0;
    }
    if (res != -1) {
        printf("%d\n", res);
    }
    return 0;
}