#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

int main()
{   int arr[100];
    int size = 0;
    int number = 0;
    scanf ("%d",  &number);
    char c;
    while (c!='\n'){
        scanf("%d%c", &arr[size], &c);
        size++;
    }
    switch(number){
        case 0:
            printf("%d\n", index_first_negative(arr, size));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, size));
            break;
        case 2:
            printf("%d\n", sum_between_negative(arr, size));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(arr, size));
            break;
        default:
            printf("Данные некорректны\n");

    }
    return 0;
}
