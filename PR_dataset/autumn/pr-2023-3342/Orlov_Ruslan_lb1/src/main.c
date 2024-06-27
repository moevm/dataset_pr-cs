#include <stdio.h>
#include <stdlib.h>

#define OUT "%d\n"

int arr[101];

int abs_max(int arr[], int size)
{
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        if (abs(arr[i]) > abs(result))
        {
            result = arr[i];
        }
    }
    return result;
}

int abs_min(int arr[], int size)
{
    int result = arr[0];
    for (int i = 0; i < size; i++)
    {
        if (abs(arr[i]) < abs(result))
        {
            result = arr[i];
        }
    }
    return result;
}

int diff(int arr[], int size)
{
    return abs_max(arr, size) - abs_min(arr, size);
}

int sum(int arr[], int size)
{
    int max = abs_max(arr, size);
    int sum = 0;
    int found_max = 0;

    for (int i = 0; i < size; i++)
    {
        if (abs(arr[i]) == abs(max))
        {
            found_max = 1;
        }

        if (found_max)
        {
            sum += arr[i];
        }
    }
    return sum;
}

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
int main()
{
    int size = 0;
    int first;
    scan_array(arr, &size, &first);
    output(first, arr, size);
    return 0;
}
