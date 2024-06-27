#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void* a, const void* b){
    const int *f = (const int *)a;
    const int *s = (const int *)b;
    if(*f > *s){
        return 1;
    }
    if(*f < *s){
        return -1;
    }
    return 0;
}

int main(){
    int arr[1000];
    int len = 1000;
    for (int i = 0;i<len;i++){
        scanf("%d",&arr[i]);
    }
    qsort(arr, len, sizeof(int), cmp);
    int zero = 0;
    clock_t bsearch_time = clock();
    int *res = (int*)bsearch(&zero,arr,len,sizeof(int),cmp);
    bsearch_time = clock()-bsearch_time;
    if(res){
        printf("exists\n");
    }else{
        printf("doesn't exist\n");
    };
    printf("%lf\n", (double)bsearch_time / CLOCKS_PER_SEC);
    
    int indicator = 0;
    clock_t bruteforce_time = clock();
    for (int i = 0;i<len;i++){
        if (arr[i]==0){
            indicator = 1;
        }
    }
    bruteforce_time = clock()-bruteforce_time;
    if (indicator){
        printf("exists\n");
    }else{
        printf("doesn't exist\n");
    };
    printf("%lf\n", (double)bruteforce_time / CLOCKS_PER_SEC);
    return 0;
}
