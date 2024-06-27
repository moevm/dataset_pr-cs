#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH_ARR 1000

void bubble_sort(int arr[])
{
    for (int i = 0; i < LENGTH_ARR - 1; i++)
    {
        for (int j = 0; j < LENGTH_ARR - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void fill_arr(int arr[])
{
    for (int i = 0; i < LENGTH_ARR; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void copy_arr(int arr_quick[], int arr[])
{
    for (int i = 0; i < LENGTH_ARR; i++)
    {
        arr_quick[i] = arr[i];
    }
}

void print_arr(int arr[])
{
    for (int i = 0; i < LENGTH_ARR; i++)
    {
        printf("%d ", arr[i]);
    }
}



void answer()
{
    int arr[LENGTH_ARR];
    int arr_quick[LENGTH_ARR];
    fill_arr(arr);
    copy_arr(arr_quick, arr);

    clock_t start_bubble = clock();
    bubble_sort(arr);
    clock_t end_bubble = clock();
    double time_bubble = ((double)(end_bubble - start_bubble)) / CLOCKS_PER_SEC;


    clock_t start_quick = clock();
    qsort(arr_quick, LENGTH_ARR, sizeof(int), compare);
    clock_t end_quick = clock();
    double time_quick = ((double)(end_quick - start_quick)) / CLOCKS_PER_SEC;

    print_arr(arr);
    printf("\n%f\n", time_bubble);
    printf("%f\n", time_quick);
}

int main()
{
    answer();
    return 0;
}