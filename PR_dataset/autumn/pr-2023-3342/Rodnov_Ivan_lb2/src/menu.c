#include <stdio.h>
#include "input_arr.h"
#include "switchres.h"
#define MAX_SIZE 100

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
