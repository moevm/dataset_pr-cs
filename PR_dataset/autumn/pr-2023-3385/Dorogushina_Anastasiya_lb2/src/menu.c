#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main(){
    int x,arr[100];
    int len = 0;
    char space;

    scanf("%d%c", &x, &space);
    do {
        scanf("%d%c", &arr[len], &space);
        len += 1;
    } while (space != '\n');

    switch(x){
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

