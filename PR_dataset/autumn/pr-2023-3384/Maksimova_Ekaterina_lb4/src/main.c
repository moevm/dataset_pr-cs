#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show_time(clock_t start_time, clock_t end_time){
    printf("%f\n", (float)(end_time - start_time)/CLOCKS_PER_SEC);
}

void cycle(int *arr){
    int flag = 0;
    clock_t start_time = clock();
    for(int i = 0; i < 1000; i++){
        if(arr[i] == 0){
            flag = 1;
        }
    }
    if (flag) printf("exists\n");
    else printf("doesn't exist\n");
    clock_t end_time = clock();
    show_time(start_time, end_time);
}

int cmp( const void *a, const void *b){
    const int *f = (const int*)a;
    const int *s = (const int*)b;
    if (*f > *s)
        return 1;
    if (*f < *s)
        return -1;
    return 0;
}

void binar_search( int *arr){
    int key = 0;
    clock_t start_time = clock();
    int *res = bsearch(&key, arr, 1000, sizeof(int), cmp);
    if (res) printf("exists\n");
    else printf("doesn't exist\n");
    clock_t end_time = clock();
    show_time(start_time, end_time);
}

int main(){
    int arr[1000]; 
    for(int i =0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, 1000, sizeof(int), cmp);
    binar_search(arr);
    cycle(arr);
    return 0;
}
