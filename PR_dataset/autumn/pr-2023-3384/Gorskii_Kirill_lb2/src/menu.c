#include <stdlib.h>
#include <stdio.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"

const char  err_msg[] = "Данные некорректны";

int main() {
    int     choice;
    int     tmp;
    char    separator;
    int     is_valid = 0;

    int arr[100];
    size_t len = 0;

    if (!scanf("%d", &choice)) {
        puts(err_msg);
        return 0;
    }
    
    while (1) {
        int n_read = scanf("%d%c", &tmp, &separator);
        
        if (n_read != 2) {
            puts(err_msg);
            return 0;
        }

        arr[len++] = tmp;
        if (separator == '\n') break;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (arr[i] < 0) {
            is_valid = 1;
            break;
        }
    }

    if (!is_valid) {
        puts(err_msg);
        return 0;
    }

    switch (choice) {
        case 0:
            printf("%ld\n", index_first_negative(arr, len));
            break;
        case 1:
            printf("%ld\n", index_last_negative(arr, len));
            break;
        case 2:
            printf("%d\n", sum_between_negative(arr, len));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(arr, len));
            break;
        default:
            puts(err_msg);
            break;
    }
}