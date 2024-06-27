#include <stdio.h>
#include <stdlib.h>


#define N 100

int abs_max(int arr[], int i);

int abs_min(int arr[], int i);

int diff(int arr[], int i);

int sum(int arr[], int i);

int main() {
    int key = 0;
    scanf("%d", &key);

    int arr[N];
    int i = 0;
    char sp = ' ';

    while (i < N && sp == ' ') {
        scanf("%d%c", &arr[i], &sp);
        i++;
    }

    switch (key) {
        case 0:
            printf("%d\n", abs_max(arr, i));
            break;
        case 1:
            printf("%d\n", abs_min(arr, i));
            break;
        case 2:
            printf("%d\n", diff(arr, i));
            break;
        case 3:
            printf("%d\n", sum(arr, i));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}

int abs_max(int arr[], int i) {
    int max = arr[0];
    for (int j = 0; j < i; j++) {
        if (abs(max) < abs(arr[j]))
            max = arr[j];
    }
    return max;
}

int abs_min(int arr[], int i) {
    int min = arr[0];
    for (int j = 0; j < i; j++) {
        if (abs(min) > abs(arr[j]))
            min = arr[j];
    }
    return min;
}

int diff(int arr[], int i) {
    return abs_max(arr, i) - abs_min(arr, i);
}

int sum(int arr[], int i) {
    int sum = 0;
    int max = abs_max(arr, i);

    int flag = 0;
    for (int j = 0; j < i; j++) {
        if (arr[j] == max) {
            sum += arr[j];
            flag = 1;
        } else if (flag == 1) {
            sum += arr[j];
        }
    }
    return sum;
}
