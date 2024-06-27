#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_size 1000

int sortProcessing(int arr[], int low, int high);

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int replacement = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = replacement;
            }
        }
    }
}

void quickSort(int arr[], int min, int max) {
    if (min < max) {
        int temporary_middle = sortProcessing(arr, min, max);
        quickSort(arr, min, temporary_middle - 1);
        quickSort(arr, temporary_middle + 1, max);
    }
}

int sortProcessing(int arr[], int min, int max) {
    int arr_end = arr[max];
    int i = (min - 1); 

    for (int j = min; j <= max - 1; j++) {
        if (arr[j] <= arr_end) {
            i++;
            int replacement = arr[i];
            arr[i] = arr[j];
            arr[j] = replacement;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[max];
    arr[max] = temp;

    return i + 1;
}

void int_scan(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

int main() {
    int arr[max_size];
    int_scan(arr, max_size);
    clock_t start_bubble = clock();
    bubbleSort(arr, max_size);
    clock_t end_bubble = clock();
    double elapsed_time_bubble = ((double)(end_bubble - start_bubble));
    clock_t start_quick = clock();
    quickSort(arr, 0, max_size - 1);
    clock_t end_quick = clock();
    double elapsed_time_quick = ((double)(end_quick - start_quick));

    for (int i = 0; i < max_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%f\n", elapsed_time_bubble);
    printf("%f\n", elapsed_time_quick);

    return 0;
}