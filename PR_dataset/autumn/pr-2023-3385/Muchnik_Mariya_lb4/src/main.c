#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void bubble_sort(int arr[], size_t size){
    for(int x = 0; x < size-1; x++){
        for(int y = 0; y < size - x - 1; y++){
            if (arr[y] > arr[y+1]) {
                int c = arr[y+1];
                arr[y+1] = arr[y];
                arr[y] = c;
            }
        }
    }
}

int cmp(const void *a, const void *b){
    const int *f = (const int *)a;
    const int *s = (const int *)b;
    if (*f > *s) return 1;
    if (*f < *s) return -1;
    return 0;
}

int main(){
    size_t size = SIZE;
    int arr[size], arr2[size];
    for (int i = 0; i < size; i++){
        scanf("%d", &arr[i]);
        arr2[i] = arr[i];
    }

    time_t t = clock();
    bubble_sort(arr, size);
    t = clock() - t;
    
    time_t qt = clock();
    qsort(arr2, size, sizeof(int), cmp);
    qt = clock() - qt;
    
    for (int i = 0; i < size; i++) printf("%d ", arr2[i]);
    printf("\n%f\n", (float)t/CLOCKS_PER_SEC);
    printf("%f\n", (float)qt/CLOCKS_PER_SEC);
}