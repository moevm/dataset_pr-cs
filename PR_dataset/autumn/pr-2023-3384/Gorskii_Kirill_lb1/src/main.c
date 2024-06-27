#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

const char  err_msg[] = "Данные некорректны";
int         arr[100];
size_t      len = 0;
size_t      first, last;

int calculate_range_abs_sum(int* arr, size_t first, size_t last) {
    int sum = 0;
    for (size_t i = first; i < last; i++)
        sum += abs(arr[i]);
    
    return sum;
}

/* 0 */
size_t index_first_negative(int* arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (arr[i] < 0)
            return i;
    }

    return SIZE_MAX;
}

/* 1 */
size_t index_last_negative(int* arr, size_t len) {
    for (size_t i = len; i > 0; i--) {
        if (arr[i - 1] < 0) 
            return i - 1;
    }
    
    return SIZE_MAX;
}

/* 2 */
int sum_between_negative(int* arr, size_t len) {
    return calculate_range_abs_sum(arr, first, last);
}

/* 3 */
int sum_before_and_after_negative(int* arr, size_t len) {
    return calculate_range_abs_sum(arr, 0, first)
         + calculate_range_abs_sum(arr, last, len);
}

int main() {
    int     choice;
    int     tmp;
    char    separator;
    int     is_valid = 0;
    
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

    first = index_first_negative(arr, len);
    last = index_last_negative(arr, len);

    switch (choice) {
        case 0:
            printf("%ld\n", first);
            break;
        case 1:
            printf("%ld\n", last);
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