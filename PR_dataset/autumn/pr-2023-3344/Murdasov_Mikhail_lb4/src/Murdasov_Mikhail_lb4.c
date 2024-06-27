#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

int cmp(const void* a, const void* b){
    const int* f = (const int*) a;
    const int* s = (const int*) b;
    if (*f < *s) return 1;
    if (*f > *s) return -1;
    return 0;
}

int main(){
    
    int numbers_array[SIZE];
    
    for(int i = 0; i < SIZE; i++){
        scanf("%d", &numbers_array[i]);
    }
    
    clock_t start = clock();
    
    qsort(numbers_array, SIZE, sizeof(int), cmp);

    clock_t stop = clock();
    
    for(int i = 0; i < SIZE; i++){
        printf("%d ", numbers_array[i]);
    }
    
    printf("\n");
    printf("%f\n", (float)(stop - start)/CLOCKS_PER_SEC);
    
    return 0;
    
}