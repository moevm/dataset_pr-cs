#include"max.h"
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