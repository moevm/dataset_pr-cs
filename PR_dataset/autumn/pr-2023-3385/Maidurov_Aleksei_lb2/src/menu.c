#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

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
        printf("%d\n", max(arr, arr_size));
        break;
    case 1:
        printf("%d\n", min(arr, arr_size));
        break;
    case 2:
        printf("%d\n", diff(arr, arr_size));
        break;
    case 3:
        printf("%d\n", sum(arr, arr_size));
        break;
    default:
        puts("Данные некорректны\n");
    }
    return 0;
}