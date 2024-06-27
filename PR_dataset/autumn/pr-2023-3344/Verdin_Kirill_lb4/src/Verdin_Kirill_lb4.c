#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LEN 1000

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

float time_bsearch(int *arr, int key)
{
    time_t start = clock();
    int *item = (int *)bsearch(&key, arr, LEN, sizeof(int), compare);
    time_t end = clock();
    if (item != NULL)
    {
        printf("exists\n");
    }
    else
    {
        printf("doesn't exist\n");
    }
    return ((float)(end - start)) / CLOCKS_PER_SEC;
}

float time_find(int *arr, int key)
{
    time_t start = clock();
    for (size_t i = 0; i < LEN; i++)
    {
        if (arr[i] == 0)
        {
            time_t end = clock();
            printf("exists\n");
            return ((float)(end - start)) / CLOCKS_PER_SEC;
        }
    }
    time_t end = clock();
    printf("doesn't exist\n");
    return ((float)(end - start)) / CLOCKS_PER_SEC;
}

int main()
{
    int arr[LEN];
    for (size_t i = 0; i < LEN; i++)
    {
        scanf("%d", &arr[i]);
    }
    qsort(arr, LEN, sizeof(int), compare);
    int key = 0;
    printf("%f\n", time_bsearch(arr, key));
    printf("%f\n", time_find(arr, key));
    return 0;
}