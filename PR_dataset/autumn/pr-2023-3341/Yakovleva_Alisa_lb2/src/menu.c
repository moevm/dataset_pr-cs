#include <stdio.h>
#include "diff.h"
#include "max.h"
#include "min.h"
#include "sum.h"
#define MAX_ARR_SIZE 100

void get_input(int* function_number, int* arr_size, int arr[])
{
    char stop = ' ';
    int i = 0;

    scanf("%d", function_number);
    while (stop != '\n')
    {
        scanf("%d%c", &arr[i], &stop);
        i++;
    }

    *arr_size = i;
}
int distribute(int function_number, int arr_size, int arr[])
{
    switch (function_number)
    {
    case 0:
        return max(arr, arr_size);
    case 1:
        return min(arr, arr_size);
    case 2:
        return diff(arr, arr_size);
    case 3:
        return sum(arr, arr_size);
    }
}

void output_result(int function_number, int arr_size, int arr[])
{
    if (function_number >= 0 && function_number < 4) printf("%d\n", distribute(function_number, arr_size, arr));
    else printf("Данные некорректны\n");
}

int main()
{
    int arr[MAX_ARR_SIZE];
    int arr_size, function_number;

    get_input(&function_number, &arr_size, arr);
    output_result(function_number, arr_size, arr);

    return 0;
}
