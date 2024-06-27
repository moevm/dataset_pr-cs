#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000
#define CLOCK_PER_SEC ((clock_t)(1000))

int cmp(const void* a, const void* b) {
    const int* first = (const int*)a;
    const int* second = (const int*)b;

    if (*first < *second) {
        return 1;
    }
    if (*first > *second) {
        return -1;
    }
    return 0;
}

void input_array(int array[N]) {
    for(int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    } 
}

void output_array(int array[N]) {
    for(int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    } 
}

int main() {
    int array[N];
    int length = sizeof(array)/sizeof(int); 

    input_array(array);
    
    clock_t start_timer = clock();
    qsort(array, length, sizeof(int), cmp);
    clock_t end_timer = clock();

    output_array(array);

    double time_used = ((double) (end_timer - start_timer)) / CLOCKS_PER_SEC;
    printf("\n%f", time_used);
    
    return 0;
}
