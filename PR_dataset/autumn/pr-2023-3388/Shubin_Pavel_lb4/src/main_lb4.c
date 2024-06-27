#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE_OF_ARRAY 1000

void bubble_sort(int array[], int size) {
    int tmp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void array_input(int array[], int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
}

void array_output(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void sorting_time_output(double time_bubble, double time_quick) {
    printf("Время сортировки пузырьком: %f секунд\n", time_bubble);
    printf("Время быстрой сортировки: %f секунд\n", time_quick);
}

double measure_bubble_sort_time(int array[], int size) {
    clock_t start_time_bubble = clock();
    bubble_sort(array, size);
    clock_t finish_time_bubble = clock();
    return ((double)(finish_time_bubble - start_time_bubble)) / CLOCKS_PER_SEC;
}

double measure_quick_sort_time(int array[], int size) {
    clock_t start_time_quick = clock();
    qsort(array, size, sizeof(int), compare);
    clock_t finish_time_quick = clock();
    return ((double)(finish_time_quick - start_time_quick)) / CLOCKS_PER_SEC;
}

int main() {
    int array[SIZE_OF_ARRAY];

    array_input(array, SIZE_OF_ARRAY);

    double time_of_bubble = measure_bubble_sort_time(array, SIZE_OF_ARRAY);
    double time_of_quick = measure_quick_sort_time(array, SIZE_OF_ARRAY);

    array_output(array, SIZE_OF_ARRAY);
    sorting_time_output(time_of_bubble, time_of_quick);

    return 0;
}
