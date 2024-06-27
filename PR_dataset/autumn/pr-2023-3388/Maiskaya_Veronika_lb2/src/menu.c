#include "print_func.h"
#include "scan_func.h"

int main()
{
    int func_value;
    int arr[N];
    int index = 0;

    read_numbers(arr, &index, N, &func_value);

    print_func(func_value, arr, index);

    return 0;
}
