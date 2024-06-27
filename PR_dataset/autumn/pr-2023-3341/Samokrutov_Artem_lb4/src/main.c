#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ARR_LEN 1000

int cmp(const void *, const void *);
void read(int *);
void time_binary_search(int *, int);
void time_linear_search(int *, int);
int *lsearch(int *, int);
void output(int *, clock_t);

int main() {
    int array[ARR_LEN];
    
    read(array);
    
    qsort(array, ARR_LEN, sizeof(int), cmp);
    
    time_binary_search(array, 0);
    time_linear_search(array, 0);
    
    return 0;
}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void read(int *arr) {
    for (int i = 0; i < ARR_LEN; i++) scanf("%i", &arr[i]);
}

void time_binary_search(int *arr, int key) {
    clock_t start = clock();
    
    int *index = (int *)bsearch(&key, arr, ARR_LEN, sizeof(int), cmp);
    
    clock_t end = clock();
    clock_t timer = end - start;
    
    output(index, timer);
}

void time_linear_search(int *arr, int key) {
    clock_t time_start = clock();
    
    int *index = (int *)lsearch(arr, 0);
    
    clock_t time_end = clock();
    clock_t timer = time_end - time_start;
    
    output(index, timer);
}

int *lsearch(int *arr, int key) {
    int *index = NULL;
    for (int i = 0; i < ARR_LEN; i++) {
        if (arr[i] == key) {
		    index = &arr[i];
		    break;
        }
    }
    
    return index;
}

void output(int *index, clock_t timer) {
    if (index)
        printf("exists\n");
    else 
        printf("doesn't exist\n");
        
    printf("%.3ld\n", timer / CLOCKS_PER_SEC);
}
