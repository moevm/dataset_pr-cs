#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int cmp(const void *key, const void *base){
    return abs(*(const int*)base)-abs(*(const int*)key);
}

int main(void){
    int arr[1000];
    int size=0;
    int i;
    for(i=0;i<1000;++i){
        scanf("%d", &arr[i]);
    }
    size=i;
    clock_t begin=clock();
    qsort(arr, size, sizeof(int), cmp);
    clock_t end=clock();
    for(int i=0;i<size;++i){
        printf("%d ", arr[i]);
    }
    printf("\n%ld", end-begin);
    return 0;
}
