#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000

int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void bubble_sort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {

                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void fill_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
}

void print_array(const int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

double measure_bubble_sort_time(int *array, int size) {
    clock_t start, end;
    start = clock();
    bubble_sort(array, size);
    end = clock();
    return ((double) (end - start));
}

double measure_qsort_time(int *array, int size) {
    clock_t start, end;
    start = clock();
    qsort(array, size, sizeof(int), compare_ints);
    end = clock();
    return ((double) (end - start));
}

int main() {
    int array[ARRAY_SIZE];
    int array_copy[ARRAY_SIZE];
    double cpu_time_used;

    fill_array(array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array_copy[i] = array[i];
    }

    cpu_time_used = measure_bubble_sort_time(array, ARRAY_SIZE);
    print_array(array, ARRAY_SIZE);
    printf("%f\n", cpu_time_used);

    cpu_time_used = measure_qsort_time(array_copy, ARRAY_SIZE);
    printf("f\n", cpu_time_used);

    return 0;
}
