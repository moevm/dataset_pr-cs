#include <stdio.h>

#define max_arr_size 100
int max(int arr[], int arr_size);
int min(int arr[], int arr_size);
int diff(int arr[], int arr_size);
int sum(int arr[], int arr_size);

int main() {
    int arr[max_arr_size];
    int operation_number;
    int arr_size = 0;

    scanf("%d", &operation_number);

    while (getchar() != '\n')
    {
        scanf("%d", &arr[arr_size]);
        arr_size++;
    }


    switch (operation_number)
    {
    case 0: printf("%d", max(arr, arr_size));
        break;
    case 1: printf("%d", min(arr, arr_size));
        break;
    case 2: printf("%d", diff(arr, arr_size));
        break;
    case 3: printf("%d", sum(arr, arr_size));
        break;
    default:printf("Данные некорректны");

    }

    return 0;
}

int max(int arr[], int arr_size)
{
    int current_max_element = 0;


    for (int i = 0; i < arr_size; i++)
    {

        if (current_max_element < arr[i])
        {
            current_max_element = arr[i];

        }
    }

    return current_max_element;
}

int min(int arr[], int arr_size)
{
    int current_min_element = 100000;


    for (int i = 0; i < arr_size; i++)
    {

        if (current_min_element > arr[i])
        {
            current_min_element = arr[i];

        }
    }

    return current_min_element;
}

int diff(int arr[], int arr_size)
{
    return (max(arr, arr_size) - min(arr, arr_size));
}

int sum(int arr[], int arr_size)
{

    int sum_elem = 0;
    int min_elem_number = 0;
    int min_elem = min(arr, arr_size);

    for (int i = 0; i < arr_size; i++)
    {
        if (min_elem == arr[i])
        {
            min_elem_number = i;
            break;

        }
    }




    for (int i = 0; i < min_elem_number; i++)
    {
        sum_elem += arr[i];

    }

    return sum_elem;
}
