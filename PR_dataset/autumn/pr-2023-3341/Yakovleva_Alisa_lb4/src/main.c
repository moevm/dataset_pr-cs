#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 1000

int compare(const void * a, const void * b)
{
  return ( *(int*)b - *(int*)a );
}

void input_arr(int* arr)
{
    for(int i = 0; i < ARR_SIZE; i++)
        scanf("%d", &arr[i]);
}

void output(int* arr, time_t start, time_t end)
{
    for(int i = 0; i < ARR_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n%d\n", difftime(end, start));
}

int main()
{
    int arr[ARR_SIZE];
    time_t start_sort, end_sort;
    input_arr(arr);
    time(&start_sort); 
    qsort(arr, ARR_SIZE, sizeof(int), compare); 
    time(&end_sort); 
    output(arr, start_sort, end_sort);
    return 0;
}
