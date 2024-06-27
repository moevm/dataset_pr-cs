#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define     N   1000

int cmp(const void *a, const void *b)
{
    const int *f = (const int *)a;
    const int *s = (const int *)b;
    if(*f > *s)
        return 1;
    if(*f < *s)
        return -1;
    return 0;
}

int main()
{
    int arr[N];
    
    for(size_t i = 0; i < N; i++)
    {
        scanf("%d ", &arr[i]);
    }
    
    int copyArr[N];
    for(size_t i = 0; i < N; i++)
    {
        copyArr[i] = arr[i];
    }
    
    clock_t startTime = clock();
    for (size_t i = 0; i < 1000; i++)
    {
        for (size_t j = 0; j < 1000 - i - 1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    clock_t endTime = clock();
    
    double differenceTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
    
    for(size_t i = 0; i < 1000; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n%lf", differenceTime);
    startTime, endTime, differenceTime = 0, 0, 0;
    
    startTime = clock();
    qsort(copyArr, N, sizeof(int), cmp);
    endTime = clock();
    differenceTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
    
    printf("\n%lf", differenceTime);
    
    return 0;
}
