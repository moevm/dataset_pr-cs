#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int arr[1000];
    
    for (int i = 0; i < 1000; i++) {
        scanf("%d", &arr[i]);
    }
    
    clock_t start = clock();
    qsort(arr, 1000, sizeof(int), compare);
    clock_t end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    for(int i; i<1000;i++){
        printf("%d ", arr[i]);
    }
    printf("\n%f", time_taken);

    
    return 0;
}
