#include <stdio.h>
#include <limits.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

#define SIZE 100

int main()
{
    int number, arr[SIZE], i = 0, result;
    char end_line;
    scanf("%d", &number);
    do{
        scanf("%d%c", &arr[i], &end_line);
        i++;
    }while (end_line != '\n' && i < SIZE);
    int arr_len = i;
    switch (number){
        case 0:
            result = max(arr, arr_len);
            printf("%d\n", result);
            break;
        case 1:
            result = min(arr, arr_len);
            printf("%d\n", result);
            break;
        case 2:
            result = diff(arr, arr_len);  
            printf("%d\n", result);
            break;
        case 3:
            result = sum(arr, arr_len);
            printf("%d\n", result);
            break;
        default:
            printf("Данные некорректны");
    } 
    return 0;
}
