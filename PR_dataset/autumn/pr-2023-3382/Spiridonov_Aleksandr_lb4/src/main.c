#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int compare(const void* a, const void* b){
    return (*(int*)a) <= (*(int*)b);
}

int main(){
    int arr[1000];
    int null = 0;
    
    for(int i = 0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    
    qsort(arr, 1000, sizeof(int), compare);
    
    for(int i = 0; i < 1000; i++){
        printf("%d ", arr[i]);
    } 
    int time = clock();
    printf("\n%f\n", (float)time/CLOCKS_PER_SEC);
}
