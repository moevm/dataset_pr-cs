#include <stdio.h>
#include <stdlib.h>
#define N 100

int abs_max(int n, int arr[], int size)
{
    int maxim, id;
    maxim = 0;
    for (int i = 0; i < size; i++)
    {
        if (abs(arr[i]) > abs(maxim))
        {
            maxim = arr[i];
            id = i;
        }
    }
    if (n == 0)
    {
        printf("%d\n", maxim);
    }
    else if (n == 2)
    {
        return maxim;
    }
    else if (n == 3)
    {
        return id;
    }
}

int abs_min(int n, int arr[], int size)
{
    int minimum;
    minimum = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (abs(arr[i]) < abs(minimum))
        {
            minimum = arr[i];
        }
    }
    if (n == 1)
    {
        printf("%d\n", minimum);
    }
    else if (n == 2)
    {
        return minimum;
    }
}

int diff(int n, int arr[], int size)
{
    int raz;
    raz = abs_max(n, arr, size) - abs_min(n, arr, size);
    printf("%d\n", raz);
}

int sum(int n, int arr[], int size)
{
    int summa = 0;
    for (int i = abs_max(n, arr, size); i < size; i++)
    {
        summa = summa + arr[i];
    }
    printf("%d\n", summa);
}
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