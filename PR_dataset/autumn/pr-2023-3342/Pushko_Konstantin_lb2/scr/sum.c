#include"sum.h"
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