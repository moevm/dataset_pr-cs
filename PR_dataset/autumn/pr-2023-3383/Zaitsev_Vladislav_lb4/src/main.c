#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000
int cmp(const void *a, const void *b){
    const int* el1 = (const int *)a;
    const int* el2 = (const int *)b;
    if (*el1 > *el2)
        return 1;
    if (*el1 < *el2)
        return -1;
    if (*el1 == *el2)
        return 0;
}
int main()
{
    int arr[N]; 
    int n = N;
    int key = 0;
    int result_search = 0; 
    clock_t t;
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    scanf("%d", &arr[N]);
    qsort(arr, n, sizeof(int), cmp);
    t = clock();
    int *result = bsearch(&key, arr, n, sizeof(int), cmp);
    t = clock() - t;
    if (result){
        printf("exists\n%ld\n", t);
    }
    else{
        printf("doesn't exist\n");
    }
    t = clock();
    for (int i = 0; i < n; i++){
        if(arr[i] == 0){
            result_search = 1;
            break;
        }
    }
    t = clock() - t;
    if (result_search){
        printf("exists\n%ld\n", t);
    }
    else{
        printf("doesn't exist\n");
    }
    return 0;
}
