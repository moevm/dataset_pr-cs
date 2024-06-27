#include <stdio.h>

int max(int arr[], int arr_size)
{
    int mx = arr[0];
    for (int i = 1; i < arr_size; ++i)
    {
        if (arr[i] > mx)
        {
            mx = arr[i];
        }
    }
    return mx;
}

int min(int arr[], int arr_size)
{
    int mn = arr[0];
    for (int i = 1; i < arr_size; ++i)
    {
        if (arr[i] < mn)
        {
            mn = arr[i];
        }
    }
    return mn;
}

int diff(int arr[], int arr_size)
{
    int d = max(arr, arr_size) - min(arr, arr_size);
    return d;
}

int sum(int arr[], int arr_size)
{
    int s = 0;
    int i = 0;
    int mn = min(arr, arr_size);
    while (arr[i] != mn)
    {
        s = s + arr[i];
        i++;
    }
    return s;
}

int main()
{
    int arr[100];
    int arr_size = 0;
    char c;
    int task_num;
    scanf("%d%c", &task_num, &c);
    do
    {
        scanf("%d%c", &arr[arr_size], &c);
        arr_size++;
    } while (c == ' ');
    switch (task_num)
    {
    case 0:
        printf("%d", max(arr, arr_size));
        break;
    case 1:
        printf("%d", min(arr, arr_size));
        break;
    case 2:
        printf("%d", diff(arr, arr_size));
        break;
    case 3:
        printf("%d", sum(arr, arr_size));
        break;
    default:
        puts("Данные некорректны");
    }
    return 0;
}