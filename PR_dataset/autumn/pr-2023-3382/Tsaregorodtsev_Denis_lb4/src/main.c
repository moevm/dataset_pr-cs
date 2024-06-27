#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void* b){
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
    clock_t s1,e1,s2,e2;
    double t1,t2;
    int arr[1000];
    int n=1000;
    int i;
    int flag=0;
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    qsort(arr, n, sizeof(int), cmp);
    int key = 0;
    s1=clock();
    int *res = (int*) bsearch(&key, arr, n, sizeof(int), cmp);
    e1=clock();
    if(res){
        printf("exists");
    }else{
        printf("doesn't exist");
    }
    t1=e1-s1;
    printf("\n%f",t1/CLOCKS_PER_SEC);
    s2=clock();
    for(i=0;i<1000;i++){
        if(arr[i]==0){
            flag=1;
            break;
        }
    }
    e2=clock();
    if(flag){
        printf("\nexists");
    }else{
        printf("\ndoesn't exist");
    }
    t2=e2-s2;
    printf("\n%f",t2/CLOCKS_PER_SEC);
}
