#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const int* a, const int* b){
    if(abs(*a)>abs(*b)){
        return -1;
    }
    if(abs(*a)<abs(*b)){
        return 1;
    }
    return 0;
}

int main(){
    int arr[1000];
    for(int i = 0; i<1000; i++){
        scanf("%d", &arr[i]);
    }
    clock_t st_t = clock();
    qsort(arr, 1000, sizeof(int), cmp);
    clock_t end_t = clock();
    float res_t = (float)(end_t-st_t)/CLOCKS_PER_SEC;
    for(int i = 0; i<1000; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%f", res_t);
    
    return 0;
}
