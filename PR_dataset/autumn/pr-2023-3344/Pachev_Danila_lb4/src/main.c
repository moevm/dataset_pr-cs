#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void* a, const void* b){
    return *(int*)a-*(int*)b;
}

int main(void){
    size_t len = 1000;
    int arr[len];
    for (size_t i = 0;i<len;i++){
        scanf("%d",&arr[i]);
    }
    qsort(arr, len, sizeof(int), compare);
    int key = 0;
    clock_t time_bsearch = clock();
    int *result = (int*)bsearch(&key, arr, len, sizeof(int), compare);
    time_bsearch = clock()-time_bsearch;
    if (result!=NULL)
        printf("exists\n");
    else
        printf("doesn't exist\n");
    printf("%lf\n", ((double)time_bsearch)/CLOCKS_PER_SEC);
    char flag = 0;
    clock_t time_loop_search = clock();
    for (size_t i = 0;i<len;i++){
        if (arr[i]==0){
            flag = 1;
            break;
        }
    }
    time_loop_search = clock()-time_loop_search;
    if (flag==1)
        printf("exists\n");
    else
        printf("doesn't exist\n");
    printf("%lf\n", ((double)time_loop_search)/CLOCKS_PER_SEC);
    return 0;
}
