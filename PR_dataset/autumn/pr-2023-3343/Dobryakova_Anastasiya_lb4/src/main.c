#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 1000

int cmp(const void* a, const void* b){
    return (*(const int*)a - *(const int*)b);
}

int main(){
    clock_t start, end;
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, SIZE, sizeof(int), cmp);
    int key = 0;
    start = clock();
    int* result = (int*)bsearch(&key, arr, SIZE, sizeof(int), cmp);
    end = clock();
    if (result != NULL){
        printf("exists");
    } else{
        printf("doesn't exist");
    }
    printf("\n%f\n", (double)(end - start)/CLOCKS_PER_SEC);
    int flag = 0;
    start = clock();
    for(int i = 0; i < SIZE; i++){
        if (arr[i] == key){
            flag = 1;
            break;
        }
    }
    end = clock();
    if (flag == 1){
        printf("exists");
    } else{
        printf("doesn't exist");
    }
    printf("\n%f\n", (double)(end - start)/CLOCKS_PER_SEC);
    return 0;
}