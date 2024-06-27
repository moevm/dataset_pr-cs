#include <stdio.h>
#include <stdlib.h>

void scan_array(int arr[], int *size, int *first)
{
    *size = 0;
    scanf("%d", first);
    while (getchar() != '\n')
    {
        scanf("%d", &arr[*size]);
        ++(*size);
    }
}