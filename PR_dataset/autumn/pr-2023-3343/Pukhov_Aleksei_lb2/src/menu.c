#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

#define N 100

int main()
{
    int arr[N], size, n;
    scanf("%d", &n);
    size = 0;
    char stop = ' ';
    while (size < N && stop != '\n')
    {
        scanf("%d%c", &arr[size++], &stop);
    }

    switch (n)
    {
    case 0:
        abs_max(0, arr, size);
        break;
    case 1:
        abs_min(1, arr, size);
        break;
    case 2:
        diff(2, arr, size);
        break;
    case 3:
        sum(3, arr, size);
        break;
    default:
        printf("Данные некорректны\n");
    }
    return 0;
}