#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int comparator(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

int *arr_reading(int *arr) {
    for (int i = 0; i < SIZE; i++)
        scanf("%d ", &arr[i]);
    return arr;
}

int *bubble_sorting(int *arr) {
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = 1; j <= i; j++) {
            if (comparator(&arr[j], &arr[j - 1])) {
                int tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return arr;
}

void output(int *arr, double bubble_sort_duration, double quick_sort_duration) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%f\n", bubble_sort_duration);
    printf("%f\n", quick_sort_duration);
}

int main() {
    int *array = malloc(SIZE * sizeof(int));
    int *arr = arr_reading(array);

    clock_t bubble_sort_start = clock();
    int *bubble_sort = bubble_sorting(arr);
    clock_t bubble_sort_stop = clock();
    double bubble_sort_duration = (((double) bubble_sort_stop - bubble_sort_start) / CLOCKS_PER_SEC);

    clock_t quick_sort_start = clock();
    qsort(arr, SIZE, sizeof(int), comparator);
    clock_t quick_sort_stop = clock();
    double quick_sort_duration = (((double) quick_sort_stop - quick_sort_start) / CLOCKS_PER_SEC);

    output(bubble_sort, bubble_sort_duration, quick_sort_duration);

    free(arr);
    return 0;
}

