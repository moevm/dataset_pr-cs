#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int comp(const void *a, const void *b){
    
    return *(const int*)b-*(const int*)a;
}

int main(){
    int num[1000];
    for(int i=0; i<1000; i++){
        scanf("%d", &num[i]);
    }
    clock_t start, stop;
    start= clock();
    qsort(&num, 1000, sizeof(int), comp);
    stop= clock();
    for(int i=0; i<1000; i++){
        printf("%d ", num[i]);
    }
    printf("\n%f", (stop-start) / CLOCKS_PER_SEC);
}