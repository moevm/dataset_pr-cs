#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *first, const void *second){
    const int f = *((const int *)first);
    const int s = *((const int *)second);
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}

int main(){
    const unsigned int cnt_arr = 1000;
    int arr[cnt_arr];

    for (int i=0; i < cnt_arr; i++){
        scanf("%d", &arr[i]);
    }

    qsort(arr, cnt_arr, sizeof(int), cmp);

    clock_t start, duration;
    int key = 0;
    
    start = clock();
    int *result = (int *)bsearch(&key, arr, cnt_arr, sizeof(int), cmp);
    duration = clock() - start;

    if (result) puts("exists");
    else puts("doesn't exist");
    printf("%f\n", ((float)duration)/CLOCKS_PER_SEC);

    start = clock();
    result = NULL; 
    for (int i=0; i < cnt_arr; i++){
        if (arr[i] == key){
            result = arr + i;
            break;
        }
    }
    duration = clock() - start;

    if (result) puts("exists");
    else puts("doesn't exist");
    printf("%f\n", ((float)duration)/CLOCKS_PER_SEC);

    return 0;
}
