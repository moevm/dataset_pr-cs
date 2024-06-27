#include "diff.h"

int diff(int n, int arr[], int size)
{
    int raz;
    raz = abs_max(n, arr, size) - abs_min(n, arr, size);
    printf("%d\n", raz);
}