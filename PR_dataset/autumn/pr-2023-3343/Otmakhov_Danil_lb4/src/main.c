#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000


void bubbleSort(int *arr, size_t size) {
    int temp;
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int objCmp(const void *a, const void *b){
    const int *obj1 = (const int *)a;
    const int *obj2 = (const int *)b;
    if (*obj1 < *obj2)
        return -1;
    if (*obj1 > *obj2)
        return 1;
    return 0;
}


int *readArr(size_t size){
    int *arr = (int *)malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++){
        scanf("%d", &arr[i]);
    }

    return arr;
}


int main(){
    size_t size = SIZE;
    double bubbleSortTimeSpent;
    double quickSortTimeSpent;
    int *arr = readArr(size);

    clock_t bubbleSortBegin = clock();
    bubbleSort(arr, size);
    clock_t bubbleSortEnd = clock();
    bubbleSortTimeSpent = (bubbleSortEnd - bubbleSortBegin) / CLOCKS_PER_SEC;

    clock_t quickSortBegin = clock();
    qsort(arr, size, sizeof(int), objCmp);
    clock_t quickSortEnd = clock();
    quickSortTimeSpent = (quickSortEnd - quickSortBegin) / CLOCKS_PER_SEC;

    for (size_t i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("%f\n", bubbleSortTimeSpent);
    printf("%f\n", quickSortTimeSpent);

    free(arr);

    return 0;
}
