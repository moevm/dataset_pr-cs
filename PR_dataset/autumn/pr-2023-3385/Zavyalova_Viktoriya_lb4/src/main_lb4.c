#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int sort_num(const void*a,const void*b);

int main()
{
    double time_spent = 0.0;
    clock_t begin = clock();
    int arr[1000];
    for(int i=0;i<1000;i++){
        scanf("%d",&arr[i]);
        
    }
    qsort(arr,1000,sizeof(int),sort_num);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    for(int i=0;i<1000;i++){
        printf("%d ",arr[i]);
    }
    
  return 0;
}

int sort_num(const void*a,const void*b){
    int x = *(int* )a;
    int y = *(int* )b;
    if (x<y){
      return 1;
    }
    if (x>y){
      return -1;
    }
    return 0;
}