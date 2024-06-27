#include "sum.h"

int sum(int *arr, int arr_size){
        int min_elem = min(arr, arr_size);
        int result = 0;
        for (int i = 0; i < arr_size; i++)
        {
                if (arr[i] == min_elem)
                {
                        break;
                }
                else
                {
                        result += arr[i];
                }
        }

        return result;
}

