#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int cmp (const void* a, const void* b){
    const int *f=(const int*)a;
    const int *s=(const int*)b;
    if (abs(*f)<abs(*s)){
        return 1;
    }
    if (abs(*f)>abs(*s)){
        return -1;
    }
    if (abs(*f)==abs(*s)){
        return 0;
    }
}

int main()
{
    int n=1000;
    int a[n];
    for (int i=0;i<n;i++){
       scanf("%d",&a[i]);
    }
    
    long int start=clock();
    qsort(a,n,sizeof(int),cmp);
    long int end=clock();
    for (int i=0;i<n;i++){
       printf("%d ",a[i]);
    }
    printf("\n%d",end-start);
}