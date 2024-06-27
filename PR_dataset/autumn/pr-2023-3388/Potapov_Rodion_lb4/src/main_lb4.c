#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a , const void *b){
    const int *numb = (const int *)a;
    const int *number = (const int *)b;
    if(*numb > *number)
        return 1;
    if (*numb < *number)
        return -1;
    return 0;
}
void func(){
    int arr[1000];
    int num = sizeof(arr) / sizeof(int);
    for (int i = 0 ; i<1000 ; i++){
        scanf("%d" , &arr[i]);
    }
    qsort(arr , num, sizeof(int) , cmp);
    
    double time_bsearch;
    double time_default_search;
    
    double start_time_bsearch = clock();
    int key = 0;
    int * result = (int*)bsearch(&key , arr , num , sizeof(int),cmp);
    double end_time_bsearch = clock();
    time_bsearch = (end_time_bsearch - start_time_bsearch) / CLOCKS_PER_SEC;
    
    if(result){
        printf("exists\n");
    }else{
        printf("doesn't exist\n");
    }
    printf("%f\n" , time_bsearch);
    
    double start_time_default_search = clock();
    int zero_in_arr = 0;
    for(int i = 0 ; i<1000;i++){
        if(arr[i] == 0){
            zero_in_arr = 1;
            break;
        }
    }
    double end_time_default_search = clock();
    time_default_search = (end_time_default_search - start_time_default_search) / CLOCKS_PER_SEC;
    
    if (zero_in_arr == 1){
        printf("exists\n");
    }else{
        printf("doesn't exist\n");
    }
    printf("%f\n",time_default_search );
}


int main(){
    
    func();
    
    return 0;
}