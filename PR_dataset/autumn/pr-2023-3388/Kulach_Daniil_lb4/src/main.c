#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LEN 1000

int cmp(const void* a, const void* b)
{
    return *(int *)a - *(int *)b;
}

void read_array(int arr[], int len)
{
    for (int i = 0; i < len; ++i)
    {
        scanf("%d", &arr[i]);
    }
}

void sort_array(int arr[], int len)
{
    qsort(arr, len, sizeof(int), cmp);
}

double binary_search(int arr[], int len, int key)
{
    double start_time = clock();
    int* required_element = (int*)bsearch(&key, arr, len, sizeof(int), cmp);
    double end_time = clock();
    double elapsed_time = (end_time - start_time) / CLOCKS_PER_SEC;

    if (required_element != NULL)
        printf("exists\n");
    else
        printf("doesn't exist\n");

    printf("%f\n", elapsed_time);
    return elapsed_time;
}

double linear_search(int arr[], int len, int key)
{
    double start_time = clock();
    int* required_element = NULL;
    for (int i = 0; i < len; ++i)
        if (arr[i] == key)
        {
            required_element = &arr[i];
            break;
        }
    double end_time = clock();
    double elapsed_time = (end_time - start_time) / CLOCKS_PER_SEC;

    if (required_element != NULL)
        printf("exists\n");
    else
        printf("doesn't exist\n");

    printf("%f\n", elapsed_time);
    return elapsed_time;
}

int main()
{
    int arr[ARRAY_LEN];

    read_array(arr, ARRAY_LEN);
    sort_array(arr, ARRAY_LEN);

    binary_search(arr, ARRAY_LEN, 0);
    linear_search(arr, ARRAY_LEN, 0);

    return 0;
}
