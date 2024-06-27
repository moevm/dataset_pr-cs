#include <stdio.h>
#include "enter_array_values.h"

int enter_array_values(int *array)
{
    int array_length = 0;
    do
    {
        scanf("%d", &array[array_length]);
        array_length++;
    } while (getchar() != '\n');
    return array_length;
}
