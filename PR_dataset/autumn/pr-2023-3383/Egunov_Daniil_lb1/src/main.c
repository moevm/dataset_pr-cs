#include <stdio.h>

#define N 100

int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int find_min(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    
    return min;
}

int calc_diff(int arr[], int size) {
    return find_max(arr, size) - find_min(arr, size);
}

int calc_sum(int arr[], int size) {
    int mn = find_min(arr, size);
    int summ = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == mn) {
            break;
        }
        summ += arr[i];
    }
    return summ;
}

void main() {
    int mode;
    int arr[N] = {};
    int size = 0;
    char end;

    scanf("%d%c", &mode, &end);
    for (int i = 0; i < N; i++) {
        scanf("%d%c", &arr[i], &end);
        size++;
        if (end == '\n') {
            break;
        }
    }
    
    switch (mode) {
        case 0:
            printf("%d\n", find_max(arr, size));
            break;

        case 1:
            printf("%d\n", find_min(arr, size));
            break;

        case 2:
            printf("%d\n", calc_diff(arr, size));
            break;

        case 3:
            printf("%d\n", calc_sum(arr, size));
            break;

        default:
            printf("Данные некорректны\n");
    }
}