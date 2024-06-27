#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 1000

int compare_values(const int* first_value, const int* second_value)
{
    return *first_value - *second_value;
}

void bubble_sort(int* array)
{
    int value;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE-1; j++)
        {
            if(array[j]>array[j+1])
            {
                value = array[j];
                array[j] = array[j+1];
                array[j+1] = value;
            }
        }
    }
}

void input(int* array)
{
    for(int i = 0; i < SIZE; i++)
    scanf("%d", &array[i]);
}

void output(int* array, double bubble_sort_time, double qsort_time)
{
    for(int i = 0; i < SIZE; i++)
    {
        if(i!=SIZE-1)
        printf("%d ", array[i]);
        else
        printf("%d", array[i]);
    }
    printf("\n%f\n", bubble_sort_time);
    printf("%f", qsort_time);
}

int main()
{
    int* array = calloc(SIZE, sizeof(int));
    int* array_copy = calloc(SIZE, sizeof(int));
    input(array);
    memcpy(array_copy, array, SIZE*sizeof(int));
    double bubble_sort_start = clock();
    bubble_sort(array);
    double bubble_sort_time = clock() - bubble_sort_start;
    double qsort_start = clock();
    qsort(array_copy, SIZE, sizeof(int), compare_values);
    double qsort_time = clock() - qsort_start;
    output(array_copy, bubble_sort_time, qsort_time);
}