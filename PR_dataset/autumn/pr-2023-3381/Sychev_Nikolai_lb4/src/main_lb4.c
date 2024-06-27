#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для сортировки массива методом пузырька
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Функция для быстрой сортировки массива
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int arr[1000];
    int i;
    clock_t startTime, endTime;

    // Ввод массива с клавиатуры
    for (i = 0; i < 1000; i++) {
        scanf("%d", &arr[i]);
    }

    // Сортировка пузырьком
    startTime = clock();
    bubbleSort(arr, 1000);
    endTime = clock();
    double bubbleSortTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    // Вывод отсортированного массива
    for (i = 0; i < 1000; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Вывод времени сортировки пузырьком
    printf("%f\n", bubbleSortTime);

    // Сортировка быстрой сортировкой
    startTime = clock();
    qsort(arr, 1000, sizeof(int), compare);
    endTime = clock();
    double quickSortTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    // Вывод отсортированного массива
    for (i = 0; i < 1000; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Вывод времени быстрой сортировки
    printf("%f\n", quickSortTime);

    return 0;
}
