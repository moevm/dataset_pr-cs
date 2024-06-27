#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 1000

void read_array(int* arr) {
    for (int i; i < ARR_SIZE; i++) {
        scanf("%d", &arr[i]);
    }
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int* zero_exists(int* arr) {
    for (int i = 0; i < ARR_SIZE; i++){
        if (arr[i] == 0) {
            return &arr[i];
        }
    }
    return NULL;
}

int main() {
    clock_t start, end;
    int* exists;
    int arr[ARR_SIZE];
    int key = 0;
    
    read_array(arr);
    
    qsort(arr, ARR_SIZE, sizeof(int), compare);
    start = clock();
    exists = bsearch(&key, arr, ARR_SIZE, sizeof(int), compare);
    end = clock();
    if (exists != NULL){
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    printf("%f\n", (float) (end - start));

    start = clock();
    exists = zero_exists(arr);
    end = clock();
    if (exists != NULL){
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    printf("%f\n", (float) (end - start));
}


