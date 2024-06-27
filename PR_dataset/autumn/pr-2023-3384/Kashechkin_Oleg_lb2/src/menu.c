#include <stdio.h>
#include <stdlib.h>

#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_before_and_after.h"
#include "sum_between.h"

const char err_msg[] = "Данные некорректны";

int main() {
    int arr[100];
    int i = 0;
    int value = 0;
    int len_arr = 0;
    int is_zero = 0;
    scanf("%d", &value);

    do {
        scanf("%d", &arr[i]);
        i++;
        len_arr++;
    } while (getchar() != '\n');

    for(i = 0; i < len_arr; i++) {
        if (arr[i] == 0) is_zero = 1;
    }

    if (is_zero == 0) return puts(err_msg);

    switch (value)
    {
    case 0:
        printf("%d", index_first_zero(arr, len_arr));
        break;
    case 1:
        printf("%d", index_last_zero(arr, len_arr));
        break;
    case 2:
        printf("%d", sum_between(arr, len_arr));
        break;
    case 3:
        printf("%d", sum_before_and_after(arr, len_arr));
        break;
    default:
        puts(err_msg);
        break;
    }

}