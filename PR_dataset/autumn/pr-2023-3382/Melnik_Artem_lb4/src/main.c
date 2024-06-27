#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b)
{
    const int *f=(const int*)a;
    const int *s=(const int*)b;
    
    if(*f < *s)
    {
        return 1;
    }
    if(*f > *s)
    {
        return -1;
    }
    if(*f == *s)
    {
        return 0;
    }
}

int main()
{
    int i=0;
    int arr[1000];
    for(i=0;i<1000;i++)
    {
        scanf("%d",&arr[i]);
    }
    clock_t start_time=clock();
    
    qsort(arr,1000,sizeof(int),cmp);
    
    clock_t end_time=clock();
    
    float qsort_time=((float)(end_time-start_time)/CLOCKS_PER_SEC);
    
    for(i=0;i<1000;i++)
    {
        printf(" %d",arr[i]);
    }
    
    printf("\n%f",qsort_time);
}