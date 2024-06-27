#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int arr[N];
    int arr_copy[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i=0; i<N; i++){
        arr_copy[i] = arr[i];
    }

    clock_t start_bubble = clock(); // Запоминаем время начала сортировки пузырьком
    bubbleSort(arr, N);
    clock_t end_bubble = clock(); // Запоминаем время окончания сортировки пузырьком
    clock_t ticks_bubble = end_bubble - start_bubble;


    clock_t start_quick = clock(); // Запоминаем время начала быстрой сортировки
    qsort(arr_copy, N, sizeof(int), cmp);
    clock_t end_quick = clock(); // Запоминаем время окончания быстрой сортировки
    clock_t ticks_quick = end_quick - start_quick;

    for (int i = 0; i < N; i++) {
        printf("%d ", arr_copy[i]);
    }
    printf("\n");
    printf("%d", ticks_bubble);
    printf("%d", ticks_quick);

    return 0;
}