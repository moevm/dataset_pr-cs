#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define LNBREAK "%d\n"

int index_first_zero(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if(arr[i] == 0)
        {
            return i;
        }
    }
}

int index_last_zero(int arr[], int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        if(arr[i] == 0)
        {
            return i;
        }
    }
}

int sum_between(int arr[], int n)
{
    int sum_between = 0;
    for (int i = index_first_zero(arr, n); i <= index_last_zero(arr, n); i++)
    {
        sum_between += abs(arr[i]);
    }
    return sum_between;
    
}

int sum_before_after(int arr[], int n)
{
    int sum_before = 0;
    int sum_after = 0;
    int sum_before_after = 0;
    for (int i = 0; i <= index_first_zero(arr, n); i++)
    {
        sum_before += abs(arr[i]);
    }
    for (int i = n - 1; i >= index_last_zero(arr, n); i--)
    {
        sum_after += abs(arr[i]);
    }
    sum_before_after = sum_before + sum_after;
    return sum_before_after;

    
}

void input_arr(int *arr, int *n)
{
	while (getchar() != '\n')
    {
        scanf("%d", &arr[(*n)++]);
    }
}

void switchres(int num_func, int *arr, int n)
{
	switch (num_func)
    {
    case 0:
        printf(LNBREAK, index_first_zero(arr, n));
        break;
    case 1:
        printf(LNBREAK, index_last_zero(arr, n));
        break;
    case 2:
        printf(LNBREAK, sum_between(arr, n));
        break;
    case 3:
        printf(LNBREAK, sum_before_after(arr ,n));
        break;
    default:
        printf("%s\n", "Данные некорректны");
        break;
    }
}

int main()
{
    int n = 0;
    int num_func;
    int arr[MAX_SIZE];
    scanf("%d", &num_func);
	input_arr(arr, &n);
	switchres(num_func, arr, n);
	return 0;
}
