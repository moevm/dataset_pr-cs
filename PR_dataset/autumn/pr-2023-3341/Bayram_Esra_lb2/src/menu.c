#include <stdio.h>
#include <stdlib.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"
#define MAX_LENGHT 100

int main()
{
    int array[MAX_LENGHT];
    int input;
    int size_array = 0;
    char space = ' ';

    scanf("%d", &input);
    while (size_array < MAX_LENGHT && space == ' ')
    {
        scanf("%d%c", &array[size_array], &space);
        size_array++;
    }

    switch (input)
    {
    case 0:
        printf("%d\n", max(array, size_array));
        break;
    case 1:
        printf("%d\n", min(array, size_array));
        break;
    case 2:
        printf("%d\n", diff(array, size_array));
        break;
    case 3:
        printf("%d\n", sum(array, size_array));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
}