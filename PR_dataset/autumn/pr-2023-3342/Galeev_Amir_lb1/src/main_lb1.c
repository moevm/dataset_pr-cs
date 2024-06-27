#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            return i;
        }
    }
    return -1;
}

int index_last_zero(int* arr, int size) {
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] == 0) {
            return i;
        }
    }
    return -1;
}

int sum_between(int* arr, int first_zero, int last_zero) {
    int sum = 0;
    if (first_zero >= 0 && last_zero >= 0) {
        for (int i = first_zero; i <= last_zero; i++) {
            sum += abs(arr[i]);
        }
    }
    return sum;
}

int sum_before_and_after(int* arr, int size, int first_zero, int last_zero) {
    int sum = 0;
    if (first_zero >= 0 && last_zero >= 0) {
        for (int i = 0; i < size; i++) {
            if (i < first_zero || i > last_zero) {
                sum += abs(arr[i]);
            }
        }
    }
    return sum;
}

int main() {
    int option;
    scanf("%d", &option);

    int arr[100];
    int size = 0;

    int num;
    while (scanf("%d", &num) == 1) {
        arr[size] = num;
        size++;
    }

    switch (option) {
        case 0:
            printf("%d\n", index_first_zero(arr, size));
            break;
        case 1:
            printf("%d\n", index_last_zero(arr, size));
            break;
        case 2:
            printf("%d\n", sum_between(arr, index_first_zero(arr, size), index_last_zero(arr, size)));
            break;
        case 3:
            printf("%d\n", sum_before_and_after(arr, size, index_first_zero(arr, size), index_last_zero(arr, size)));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }

    return 0;
}
