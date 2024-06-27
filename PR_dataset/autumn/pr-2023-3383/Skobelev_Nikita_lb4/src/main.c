//created by niks (student LETI)

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int cmplow(const void* first, const void* second){
    if(*(int*)first < *(int*)second)return 1;
    if(*(int*)first == *(int*)second)return 0;
    if(*(int*)first > *(int*)second)return -1;
}

int main(){
    int arr[1000];
    for(int i=0;i<1000;++i){
        scanf("%d",&arr[i]);
    }
    int time = clock();
    qsort(arr,1000,sizeof(int),cmplow);
    time = clock()-time;
    for(int i =0;i<1000;++i){
        printf("%d ",arr[i]);
    }
    printf("\n%d",time);
    return 0;
}