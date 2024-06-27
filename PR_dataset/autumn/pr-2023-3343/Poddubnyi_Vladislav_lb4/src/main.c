#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const int *i, const int *j){
    return *i-*j;
};

int main(){
    int arr[1000];
    for (int i = 0; i < 1000; i++) {
        scanf("%d",&arr[i]);
    }
    qsort(arr,1000, sizeof(int), (int(*) (const void *, const void *)) compare);
    clock_t startTime = clock();
    int key = 0;
    int* zeroContains = bsearch(&key, arr, 1000, sizeof(int), (int(*) (const void *, const void *)) compare);
    clock_t endTime = clock();
    if (zeroContains) printf("exists\n");
    else printf("doesn't exist\n");
    printf( "%long\n",(endTime - startTime));
    int zeroContainsTwo=0;
    startTime = clock();
    for (int i = 0; i < 1000; i++) {
        if (arr[i]==0) zeroContainsTwo=1;
    }
    endTime = clock();
    if(zeroContainsTwo==1) printf("exists\n");
    else printf("doesn't exist\n");
    printf( "%long\n",(endTime - startTime));
    return 0;
}