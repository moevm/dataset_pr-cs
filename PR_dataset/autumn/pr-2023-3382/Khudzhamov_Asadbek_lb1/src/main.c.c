#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            return i;
        }
    }
    return -1;
}

int index_last_zero(int arr[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] == 0) {
            return i;
        }
    }
    return -1;
}

int sum_between(int arr[], int start, int end) {
    if (start == -1 || end == -1) {
        return 0;
    }
    int sum = 0;
    for (int i = start + 1; i < end; i++) {
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_and_after(int arr[], int start, int end, int size) {
    if (start == -1 || end == -1) {
        return 0;
    }
    int sum_before = 0;
    int sum_after = 0;

    for (int i = 0; i < start; i++) {
        sum_before += abs(arr[i]);
    }

    for (int i = end + 1; i < size; i++) {
        sum_after += abs(arr[i]);
    }

    return sum_before + sum_after;
}

int main() {
    int choice;
    scanf("%d", &choice);

    int *arr = NULL;
    int size = 0;

    while (1) {
        int num;
        if (scanf("%d", &num) != 1) {
            break;
        }
        size++;
        arr = (int *)realloc(arr, size * sizeof(int));
        arr[size - 1] = num;
    }

    int start = index_first_zero(arr, size);
    int end = index_last_zero(arr, size);

    if (choice == 0) {
        printf("%d\n", start);
    } else if (choice == 1) {
        printf("%d\n", end);
    } else if (choice == 2) {
        int result = sum_between(arr, start, end);
        printf("%d\n", result);
    } else if (choice == 3) {
        int result = sum_before_and_after(arr, start, end, size);
        printf("%d\n", result);
    } else {
        printf("Данные некорректны\n");
    }
    
    return 0;
}
