#include"diff.h"
#include"max.h"
#include"min.h"
int diff(int arr[], int arr_size)
{
    return (max(arr, arr_size) - min(arr, arr_size));
}