#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int cmp(const void* a, const void* b)
{
    if(*(const int*)a > *(const int*)b)
    {
        return 1;
    }
    if(*(const int*)a < *(const int*)b)
    {
        return -1;
    }
    return 0;
}

int main()
{
    int array[N];
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &array[i]);
    }
    
    qsort(array, N, sizeof(int), cmp);
    
    float Time0 = clock()*CLOCKS_PER_SEC;
    int search_element = 0;
    int* search_result = (int*)bsearch(&search_element, array, N, sizeof(int), cmp);
    float Time1 = clock()*CLOCKS_PER_SEC;
    
    if(search_result)
    {
        printf("exists");
    }
    else
    {
        printf("doesn't exist");
    }
    printf("\n%f\n", (Time1-Time0));
    
    float Time2 = clock()*CLOCKS_PER_SEC;
    int flag = 0;
    for(int i = 0; i < N; i++)
    {
        if(array[i] == 0)
        {
            flag = 1;
            break;
        }
    }
    float Time3 = clock()*CLOCKS_PER_SEC;
    
    if(flag)
    {
        printf("exists");
    }
    else
    {
        printf("doesn't exist");
    }
    printf("\n%f\n", (Time3-Time2));
    return 0;
}