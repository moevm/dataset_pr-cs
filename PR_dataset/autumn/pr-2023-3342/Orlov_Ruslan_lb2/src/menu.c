#include <stdio.h>
#include <stdlib.h>
#include "output.h"
#include "scan_array.h"
int arr[101];

int main()
{
    int size = 0;
    int first;
    scan_array(arr, &size, &first);
    output(first, arr, size);
    return 0;
}