#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *x1, const void *x2)
{
    return (*(int *)x2 - *(int *)x1);
}

int main(){
    int array[1000];
    for(int i=0;i<1000;i++)
    {
        scanf("%d",&array[i]);
    }
    clock_t start,stop;
    start=clock();
    qsort(array, 1000, sizeof(int), compare);
    stop=clock();
    for (int i = 0; i < 1000; i++)
    {
        if (i == 999)
            printf("%d\n", array[i]);
        else
            printf("%d ", array[i]);
    }
    printf("%ld",(stop-start)/CLOCKS_PER_SEC);
    return 0;
}