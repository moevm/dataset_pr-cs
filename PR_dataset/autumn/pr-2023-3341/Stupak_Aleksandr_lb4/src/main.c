#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

int cmp(const void *a,const void *b){
    return (const int*) a - (const int*) b;
}

void input_array(int *size, int array[], int array_copy[]) {
    char end = ' ';
    while ((*size < N) && (end != '\n')){
        scanf("%i%c", &array[*size], &end);
        array_copy[*size] = array[(*size)++];
    }
}

size_t measure_bubble_sort(int array[], int size) {
    time_t begin = time(NULL);
    for (int j = 0; j < size; j++ ){
        for (int i = 0; i < size-1;i++){
            if (array[i] > array[i + 1]){
                int x = array[i];
                array[i] = array[i + 1];
                array[i + 1] = x;
            }
        }
    }
    time_t end = time(NULL);
    return end - begin;
}

size_t measure_qsort(int array_copy[], int size) {
    time_t begin = time(NULL);
    qsort(array_copy, size, sizeof(int), cmp);
    time_t end = time(NULL);
    return end - begin;
}

void output_results(int array[], int size, size_t time_bubble_sort, size_t time_qsort) {
    for (int i = 0; i < size;i++){
        printf("%i ", array[i]);
    }
    printf("\n%ld\n%ld", time_bubble_sort, time_qsort);
}

int main(){
    int array[N],array_copy[N], size;
    size = 0;
    input_array(&size, array, array_copy);

    size_t time_bubble_sort = measure_bubble_sort(array, size);
    size_t time_qsort = measure_qsort(array_copy, size);

    output_results(array, size, time_bubble_sort, time_qsort);
}
