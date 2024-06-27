#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void * x1, const void * x2)   
{
  return ( *(int*)x1 - *(int*)x2 );
}  

int main()
{
    double time_spent = 0.0;
    int arr[1000];
    for(int i=0;i<1000;i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr,1000,sizeof(int), compare);
    int key=0;
    clock_t begin = clock();
    int *ind_elem = bsearch(&key, arr, 1000, sizeof(int), compare);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    if(ind_elem!=NULL){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", time_spent);
    int flag=0;
    clock_t begin2 = clock();
    for(int i;i<1000;i++){
        if (arr[i]==0){
            flag=1;
        }
    }
    clock_t end2 = clock();
    double time_spent2=0.0;
    time_spent2 += (double)(end2 - begin2) / CLOCKS_PER_SEC;
    if(flag==1){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", time_spent2);
}
