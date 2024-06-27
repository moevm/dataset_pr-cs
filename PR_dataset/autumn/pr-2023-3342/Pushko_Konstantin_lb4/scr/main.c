#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE_OF_ARRAY 1000

int compare(const void* a, const void* b)
{
    const int* first = (const int*) a;
    const int* second = (const int*) b;

    if (*first  >= *second ){
        return -1;
    }
    if (*first  < *second ){
        return 1;
    }
    return 0;
}


void input(const int* arr)
{
    for (int i = 0; i < SIZE_OF_ARRAY; ++i) {
        scanf("%d",&arr[i]);
    }
}

void output(double time_dif, int* arr)
{
    for (int i = 0; i < SIZE_OF_ARRAY; ++i) {
        printf("%d ",arr[i]);
    }
    printf("\n%f",time_dif);
}

int main()
{
    int arr[SIZE_OF_ARRAY];
    input(arr);

    clock_t begin = clock();
    qsort(arr,SIZE_OF_ARRAY,sizeof(int),compare);
    clock_t end = clock();
    output((double)begin-end,arr);
    
}