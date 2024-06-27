#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compar (const void* a, const void* b){
    return - (*(int*)a - *(int*)b);
}

int main(){
    int arr[1000];
    clock_t time;
    for (int i = 0; i < 1000; i++){
        scanf("%i", &arr[i]);
    }
    time = clock();
    qsort(arr, 1000, sizeof(int), compar);
    time = clock() - time;
    for (int i = 0; i < 1000; i++){
        printf("%i ", arr[i]);
    }
    //printf("%i clocks, %f seconds", (int)time, ((float)time)/CLOCKS_PER_SEC);
    return 0;
}