#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

int cmp(const void *a,const void *b){
    const int* f = (const int*) a;
    const int* s = (const int*) b;
    if (f > s){
        return 1;
    }
    if (f < s){
        return -1;
    }
    return 0;
}

int main(){
    int arr[N],arr1[N], size;
    size = 0;
    char end = ' ';
    while ((size < N) && (end != '\n')){
        scanf("%i%c", &arr[size], &end);
        arr1[size] = arr[size++];
    }
    time_t begin = time(NULL);
    for (int j = 0; j < size; j++ ){
        for (int i = 0; i < size-1;i++){
            if (arr[i] > arr[i+1]){
                int x = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = x;
            }
        }
    }
    time_t endpz = time(NULL);
    qsort(arr1,size,sizeof(int),cmp);
    time_t endqs = time(NULL);
    for (int i = 0; i < size;i++){
        printf("%i ", arr[i]);
    }
    printf("\n%ld\n%ld", endpz - begin,endqs - endpz);

}