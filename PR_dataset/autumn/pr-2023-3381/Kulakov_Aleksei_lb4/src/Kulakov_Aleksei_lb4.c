#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int comp(const int *a, const int *b){
    return -1 * (*a - *b);
}
int main() {
    int arr[1000];
    for(int i = 0; i < 1000;i++){
        scanf("%d", &arr[i]);
    }
    clock_t start = clock();
    qsort(arr,1000,sizeof(int), comp);
    clock_t end = clock();
    for(int i = 0; i < 1000;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%f", ((double)(end - start))/CLOCKS_PER_SEC);
}