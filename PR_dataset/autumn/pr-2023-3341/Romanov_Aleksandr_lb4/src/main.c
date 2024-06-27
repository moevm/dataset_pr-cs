#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

void input(int* arr);
void output(int* arr);
int comp(const void *a, const void *b);

int main(){
    int* arr = (int*)malloc(SIZE*sizeof(int));
    input(arr);
    int start = clock();

    qsort(arr, SIZE, sizeof(int), comp);
    int finish = clock();

    output(arr);
    //printf("%ld\n", (finish - start)/CLOCKS_PER_SEC);
    //вывод времени закомментирован, т.к. на moodle он не требуется
}

void input(int* arr){
    for(int i = 0; i<SIZE; i++){
        scanf("%d", &arr[i]);
    }
}

void output(int* arr){
    for (int i = 0; i<SIZE; i++){
        printf("%d ", arr[i]);
    }
}

int comp(const void *a, const void *b){
    const int* first = (const int*)a;
    const int* second = (const int*)b;
    if (abs(*first) > abs(*second)){
        return -1;
    }
    if (abs(*first) < abs(*second)){
        return 1;
    }
    return 0;
}
