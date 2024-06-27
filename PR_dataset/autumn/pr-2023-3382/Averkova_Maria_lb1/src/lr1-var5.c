#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ARRAY_SIZE 100

int findIndexOfAbsMax(int arr[], int arr_len);
int findIndexOfAbsMin(int arr[], int arr_len);
int calculateDifference(int arr[], int arr_len, int ind_max, int ind_min);
int calculateSumAfterAbsMax(int arr[], int arr_len, int ind_max);

int main() {
    int ind_max, ind_min;
    int arr[MAX_ARRAY_SIZE];
    int key;
    char space;
    int k = 0;

    scanf("%d%c", &key, &space);
    do {
        scanf("%d%c", &arr[k], &space);
        k++;
    } while (space != '\n');

    int arr_len = k;

    switch (key) {
        case 0:
            printf("%d\n", arr[findIndexOfAbsMax(arr, arr_len)]);
            break;
        case 1:
            printf("%d\n", arr[findIndexOfAbsMin(arr, arr_len)]);
            break;
        case 2:
            ind_max = findIndexOfAbsMax(arr, arr_len);
            ind_min = findIndexOfAbsMin(arr, arr_len);
            printf("%d\n", calculateDifference(arr, arr_len, ind_max, ind_min));
            break;
        case 3:
            ind_max = findIndexOfAbsMax(arr, arr_len);
            printf("%d\n", calculateSumAfterAbsMax(arr, arr_len, ind_max));
            break;
        default:
            printf("Данные некорректны\n");
    }
}

int findIndexOfAbsMax(int arr[], int arr_len) {
    int abs_max = 0;
    int ind_max;

    for (int i = 0; i < arr_len; i++) {
        if (abs(arr[i]) > abs_max) {
            abs_max = abs(arr[i]);
            ind_max = i;
        }
    }

    return ind_max;
}

int findIndexOfAbsMin(int arr[], int arr_len) {
    int abs_min = abs(INT_MAX);
    int ind_min;

    for (int i = 0; i < arr_len; i++) {
        if (abs(arr[i]) < abs_min) {
            abs_min = abs(arr[i]);
            ind_min = i;
        }
    }

    return ind_min;
}

int calculateDifference(int arr[], int arr_len, int ind_max, int ind_min) {
    return arr[ind_max] - arr[ind_min];
}

int calculateSumAfterAbsMax(int arr[], int arr_len, int ind_max) {
    int sum = 0;

    for (int i = ind_max; i < arr_len; i++) {
        sum += arr[i];
    }

    return sum;
}