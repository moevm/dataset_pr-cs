#include <stdio.h>
#include <stdlib.h>
#define N 100
#define OUTPUT_ERROR_STRING "Данные некорректны"

int abs_max(int arr[], int size) {
    int max = -99999, id_max = 0;
    for (int i = 0; i < size; i++) {
        if (abs(arr[i]) > max){
            max = abs(arr[i]);
            id_max = i;
        }
    }
    //return id_max;
    printf("%d", arr[id_max]);
}

int abs_min(int arr[], int size) {
    int min = 99999, id_min = 0;
    for (int i = 0; i < size; i++) {
        if (abs(arr[i]) < min){
            min = abs(arr[i]);
            id_min = i;
        }
    }
    printf("%d", arr[id_min]);
}

int diff(int arr[], int size, int max, int min) {
    printf("%d", arr[max] - arr[min]);
}

int sum(int arr[], int size, int max) {
    int sum = 0;
    for (int i = max; i < size; i++) {
        sum = sum + arr[i];
    }
    printf("%d", sum);
}
int id_max(int arr[], int size){
    int max = -99999, id_max = 0;
    for (int i = 0; i < size; i++) {
        if (abs(arr[i]) > max){
            max = abs(arr[i]);
            id_max = i;
        }
    }
    return id_max;
}
int id_min(int arr[], int size){
    int max = 99999, id_min = 0;
    for (int i = 0; i < size; i++) {
        if (abs(arr[i]) < max){
            max = abs(arr[i]);
            id_min = i;
        }
    }
    return id_min;
}

int main() {
    int operation, size = 0, arr[N];
    char space =' ';
    scanf("%d", &operation);
    while (size < N && space == ' ') {
        scanf("%d%c", &arr[size], &space);
        size++;
    }
    int max = id_max(arr, size), min = id_min(arr, size);
    switch (operation) {
        case 0:
            abs_max(arr, size);
            break;
        case 1:
            abs_min(arr, size);
            break;
        case 2:
            diff(arr, size, max, min);
            break;
        case 3:
            sum(arr, size, max);
            break;
        default:
            printf("%s", OUTPUT_ERROR_STRING);
            break;
    }
}