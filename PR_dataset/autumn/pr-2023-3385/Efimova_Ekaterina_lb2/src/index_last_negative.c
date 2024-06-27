#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int index_last_negative(int arr[], int size)
{   int i;
    for (i = size-1; i >= 0; i--)
    if (arr[i] < 0)
        return i;
}
       
