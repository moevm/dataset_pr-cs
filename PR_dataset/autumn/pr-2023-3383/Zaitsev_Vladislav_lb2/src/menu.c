#include <stdio.h>
#define N 100
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main()
{
    int opperation, len = 0;
    int arr[N];
    char end_l; 
    scanf("%d%c", &opperation, &end_l);
    while (end_l != '\n'){
        scanf("%d%c", &arr[len], &end_l);
        len++;
    }
    switch (opperation){
        case 0:
            printf("%d\n", index_first_even(arr, len));
            break;
        case 1:
            printf("%d\n", index_last_odd(arr, len));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr, len));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(arr, len));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}
