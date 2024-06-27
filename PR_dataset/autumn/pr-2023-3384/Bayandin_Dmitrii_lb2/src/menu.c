#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_before_and_after.h"
#include "sum_between.h"

int main(){
    int num;
    scanf("%d", &num);
    if (num != 0 && num != 1 && num != 2 && num != 3){
        printf("Данные некорректны");
        return 0;
    }
    int arr_end[100];
    char str = ' ';
    int quantity = 0;
    for (quantity; (quantity < 100 && str != '\n'); ++quantity){
        scanf("%d%c", &arr_end[quantity], &str);
        }
    switch (num){
    case 0:
        printf("%d\n", index_first_zero(quantity, arr_end));
        break;
    case 1:
        printf("%d\n", index_last_zero(quantity-1, arr_end));
        break;
    case 2:
        printf("%d\n", sum_between(quantity, arr_end));
        break;
    case 3:
        printf("%d\n", sum_before_and_after(quantity, arr_end));
        break;
    }
    return 0;
}