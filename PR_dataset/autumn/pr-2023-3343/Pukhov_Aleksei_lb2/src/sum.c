#include "sum.h"

int sum(int n, int arr[], int size)
{
    int summa = 0;
    for (int i = abs_max(n, arr, size); i < size; i++)
    {
        summa = summa + arr[i];
    }
    printf("%d\n", summa);
}