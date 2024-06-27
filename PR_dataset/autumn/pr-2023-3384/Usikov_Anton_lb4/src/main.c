#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp (const void* a, const void* b){
    const int *q = (const int*)a;
    const int *w = (const int*)b;
    if (*q>*w)
    return -1;
    if (*q<=*w)
    return 1;
}

int main(){
    clock_t start, fin;
    int arr[1000];
    int null = 0;
    for (int i = 0; i < 1000; i++)
    scanf("%d ", &arr[i]);
    start = clock();
    qsort(arr, 1000, sizeof(int), cmp);
    fin = clock();
    for (int i = 0; i < 1000; i++)
    printf("%d ", arr[i]);
    printf("\n%ld", (fin - start)/CLOCKS_PER_SEC);
    return 0;
}