#include <stdio.h>
#define MAX_ARR_SIZE 100

int max(int arr[], int arr_size)
{
    int max = arr[0], i;
    for (i = 1; i < arr_size; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

int min(int arr[], int arr_size)
{
    int min = arr[0], i;
    for (i = 1; i < arr_size; i++)
        if (arr[i] < min) min = arr[i];
    return min;
}

int diff(int arr[], int arr_size)
{
    return max(arr, arr_size) - min(arr, arr_size);
}

int sum(int arr[], int arr_size)
{
    int min_arr_element = min(arr, arr_size);
    int min = min_arr_element;
    int sum_up_to_the_first_min = 0, i = 0;

    while (arr[i] != min)
    {
        sum_up_to_the_first_min += arr[i];
        i++;
    }
    return sum_up_to_the_first_min;
}

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
