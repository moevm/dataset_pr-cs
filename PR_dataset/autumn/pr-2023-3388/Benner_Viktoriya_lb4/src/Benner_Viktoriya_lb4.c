#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE 1000

int compare_numbers(const void *a, const void *b);
void sort_array_with_time(int *arr, double *time);
void read_input_to_array(int *arr);
void print_sorted_array(const int *arr, double time);

int compare_numbers(const void *a, const void *b) {
    const int *first = (const int *)a;
    const int *second = (const int *)b;
    return (*first < *second) ? 1 : (*first > *second) ? -1 : 0;
}

void sort_array_with_time(int *arr, double *time) {
    clock_t start_time = clock();
    qsort(arr, ARRAY_SIZE, sizeof(int), compare_numbers);
    clock_t finish_time = clock();
    *time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
}

void read_input_to_array(int *arr) {
    int len = 1000 * ARRAY_SIZE;
    char *input = (char *)malloc(len);
    fgets(input, len, stdin);
    char *token = strtok(input, " ");
    int num_index = 0;
    while (token) {
        arr[num_index] = atoi(token);
        token = strtok(NULL, " ");
        num_index++;
    }
    free(input);
}

void print_sorted_array(const int *arr, double time) {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[ARRAY_SIZE - 1]);
    printf("%f", time);
}

int main() {
    int *arr = (int *)malloc(ARRAY_SIZE * sizeof(int));
    read_input_to_array(arr);

    double time_of_sort;
    sort_array_with_time(arr, &time_of_sort);
    print_sorted_array(arr, time_of_sort);

    free(arr);  // освобождение выделенной памяти

    return 0;
}