#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
#define OUT "%d\n"

int output(int first, int arr[], int size)
{
    switch (first)
    {
    case 0:
        printf(OUT, abs_max(arr, size));
        break;
    case 1:
        printf(OUT, abs_min(arr, size));
        break;
    case 2:
        printf(OUT, diff(arr, size));
        break;
    case 3:
        printf(OUT, sum(arr, size));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
    return 0;
}