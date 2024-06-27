#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CNT 1000

int cmp_sort(const void* a, const void* b){
    return *(int*)a>*(int*)b;
}

int cmp_search(const void* a, const void* b){
    return *(int*)a>*(int*)b?1:( *(int*)a==*(int*)b?0:-1);
}

void print_time_and_existence(clock_t stime,int exist){
    printf("%s\n",exist?"doesn't exist":"exists");
    printf("%f\n",(float)stime / CLOCKS_PER_SEC);
}

int main(){
    int array[CNT];
    for(size_t i = 0;i<CNT;i++){
        scanf(" %d",&array[i]);
    }
    qsort(array,CNT,sizeof(int),cmp_sort);
    clock_t stime;
    int key = 0;
    stime = clock();
    int* r = bsearch(&key,array,CNT,sizeof(int),cmp_search);
    stime = clock() - stime;
    print_time_and_existence(stime,r==NULL);
    stime = clock();
    int f = 0;
    stime = clock();
    for(size_t i = 0;i<CNT;i++){
        if(array[i]==key){
            f = 1;
            break;
        }
    }
    stime = clock() - stime;
    print_time_and_existence(stime,!f);
    return 0;
}