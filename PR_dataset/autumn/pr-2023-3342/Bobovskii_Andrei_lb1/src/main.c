#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMBER 0
#define MIN_NUMBER 1000


int max(int *arr, int len)
{
    int count, max_number = MAX_NUMBER;
    for (count = 0; count < len; count++)
        if (arr[count] > max_number)
            max_number = arr[count];
    return max_number;
}
int min(int *arr, int len)
{
    int count, min_number = MIN_NUMBER;
    for (count = 0; count < len; count++)
        if (arr[count] < min_number)
            min_number = arr[count];
    return min_number;
}
int diff(int *arr, int len)
{
    return max(arr, len) - min(arr, len);
}
int sum(int *arr, int len)
{
    int min_number, summ = 0, count;
    min_number = min(arr, len);
    for (count = 0; count < len; count++)
    {
        if (arr[count]!=min_number)
            summ+= arr[count];
        else
            break;
    }
    return(summ);
}

int Input(int **arr)
{
    int count, number, len = 0;
    char space;
    scanf("%c", &space);
    for (count = 0; space != '\n'; ++count, ++len)
    {
        scanf("%d%c", &number, &space);
        (*arr)[count] = number;
    }
    return len;
}

void Output(int **arr, int len, int key)
{
    switch (key)
    {
        case 0:
            printf ("\n%d", max(*arr, len));
            break;
        case 1:
            printf ("\n%d", min(*arr, len));
            break;
        case 2:
            printf ("\n%d", diff(*arr, len));
            break;
        case 3:
            printf ("\n%d", sum(*arr, len));
            break;
        default:
            printf ("\n%s\n", "Данные некорректны");
    }
}

int main()
{
    int key, len;
    int *arr;
    scanf("%d", &key);
    len = Input(&arr);
    Output(&arr, len, key);
    return 0;
}
