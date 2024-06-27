#include <stdio.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

#define N 100

int main(){
    int arr[N];
    int mode;
    int n = 0;
    char c;
    scanf("%d%c",&mode, &c);
    do{
        scanf("%d%c", &arr[n], &c);
        n++;
    } while (c != '\n');
    switch (mode){
        case 0:
            printf("%d\n", index_first_negative(arr, n));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, n));
            break;
        case 2:
            printf("%lld\n", sum_between_negative(arr, n));
            break;
        case 3:
            printf("%lld\n", sum_before_and_after_negative(arr, n));
            break;
        default:
            printf("Данные некорректны");
    }
}

