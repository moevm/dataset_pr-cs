#include "scan_func.h"

void read_numbers(int arr[], int *index, int size, int *func_value)
{
    scanf("%d", func_value);

    while (1)
    {
        scanf("%d", &arr[*index]);
        (*index)++;
        char c = getchar();
        if (c == '\n')
            break;
    }
}
