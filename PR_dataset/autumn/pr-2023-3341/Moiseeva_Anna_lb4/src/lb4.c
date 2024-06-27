#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARR_LEN 1000

int cmp(const void *a, const void *b){
    const int *f = (const int *)a;
    const int *s = (const int *)b;
    if (abs(*f) > abs(*s)){
        return -1;
    }
    if (abs(*f) < abs(*s)){
        return 1;
    }
    return 0;
}

void input_arr(int arr[]){
    for (int i = 0; i < ARR_LEN; i++){
        scanf("%d", &arr[i]);
    }
}

void output_arr(int arr[], int seconds){
    for (int j = 0; j < ARR_LEN; j++){
        printf("%d ", arr[j]);
    }
    printf("\n");
    printf("%d", seconds);
    printf("\n");
}

int main(){
    time_t sort_time = time(NULL);
    int arr[ARR_LEN];
    input_arr(arr);
    qsort(arr, ARR_LEN, sizeof(int), cmp);
    sort_time = time(NULL) - sort_time;
    output_arr(arr, sort_time);
    return 0;
}