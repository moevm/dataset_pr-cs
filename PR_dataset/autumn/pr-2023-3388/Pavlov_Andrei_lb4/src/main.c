#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define INPUT_ARRAY_SIZE 1000
#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000.)

void parse_data(int* first_array, int* second_array) {
    for (int i = 0; i < INPUT_ARRAY_SIZE; i++) {
        scanf("%d", &first_array[i]);
        second_array[i] = first_array[i];
    }
}

int compare(const void* left_pointer, const void* right_pointer) {
    const int* left  = (const int *)left_pointer;
    const int* right = (const int *)right_pointer;

    return (*left > *right) - (*left < *right);
}

void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

float bubble_sort_benchmark(int* array) {
    clock_t t_start = clock();

    bool swapped;
    for (int i = 0; i < INPUT_ARRAY_SIZE - 1; i++) {
        swapped = false;
        for (int j = 0; j < INPUT_ARRAY_SIZE - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                swapped = true;
            }
        }
 
        if (swapped == false)
            break;
    }

    clock_t t_end = clock();
    return (t_end - t_start) / CLOCKS_PER_MSEC;
}

float qsort_benchmark(int* array) {
    clock_t t_start = clock();
    qsort(array, INPUT_ARRAY_SIZE, sizeof(int), compare);
    clock_t t_end = clock();

    return (t_end - t_start) / CLOCKS_PER_MSEC;
}

void print_data(int* array) {
    for (int i = 0; i < INPUT_ARRAY_SIZE; i++)
        printf("%d ", array[i]);
}

void print_time(float time) {
    printf("\n%.2f ms", time);
}

int main() {
    int input[INPUT_ARRAY_SIZE] = { 0 }, input_copy[INPUT_ARRAY_SIZE] = { 0 };
    parse_data(input, input_copy);

    float btime = bubble_sort_benchmark(input);
    float qtime = qsort_benchmark(input_copy);

    print_data(input_copy);
    print_time(btime);
    print_time(qtime);
}
