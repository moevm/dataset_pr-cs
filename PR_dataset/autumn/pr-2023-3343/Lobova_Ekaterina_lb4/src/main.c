#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

void bubblesort(int* arr, size_t n){
    int tmp;
    for (int i = n - 1; i>=0;i--){
        for (int j = 1; j <=i; j++){
            if (arr[j]<=arr[j-1]){
                tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
            }
        }
    }
}

int compar(const void* a, const void* b){
    return *((int*)a) -*((int*)b);
}

int main(){
    int arr [SIZE];
    int arrcopy[SIZE];
    int elem;
    for (int i = 0; i<SIZE;i++){
        scanf("%i",&elem);
        arr[i]=elem;
        arrcopy[i]=elem;
    }

    clock_t start1 = clock();
    bubblesort(arr,SIZE);
    clock_t end1 = clock();

    clock_t start2 = clock();
    qsort(arrcopy, SIZE, sizeof(int), compar);
    clock_t end2 = clock();

    for (int i = 0; i<SIZE; i++){
        printf("%i ",arrcopy[i]);
    }

    printf("\n%f",(double)(end1-start1)/CLOCKS_PER_SEC);
    printf("\n%f",(double)(end2-start2)/CLOCKS_PER_SEC);
    return 0;
}
