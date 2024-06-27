#include <stdio.h>
#include <stdlib.h>

const char err_msg[] = "Данные некорректны";

int index_last_zero(int* arr, int len_arr) {
    int last_zero, i;

    for (i = len_arr-1; i > 0; i--) {
        if (arr[i] == 0) {
            last_zero = i;
            break;
        }
    }
    return last_zero;
}

int index_first_zero(int* arr, int len_arr) {
    int first_zero, i;

    for (i=0; i < len_arr; i++) {
        if (arr[i] == 0) {
            first_zero = i;
            break;
        }
    }
    return first_zero;
}

int sum_between(int* arr, int len_arr, int first_zero, int last_zero) {
    int i, sum = 0;

    for (i = first_zero; i < last_zero; i++) {
        sum += abs(arr[i]);
    }

    return sum;
}

int sum_before_and_after(int* arr, int len_arr, int first_zero, int last_zero) {
    int i, sum = 0;

    for (i = 0; i < first_zero; i ++) {
        sum += abs(arr[i]);
    }

    for (i = last_zero; i < len_arr; i++) {
        sum += abs(arr[i]);
    }

    return sum;
}

void tasks(int* arr, int len_arr, int value) {

    int first_zero = index_first_zero(arr, len_arr);
    int last_zero = index_last_zero(arr, len_arr);

    switch (value) {
        case 0:
            printf("%d", first_zero);
            break;
        case 1:
            printf("%d", last_zero);
            break;
        case 2:
            printf("%d", sum_between(arr, len_arr, first_zero, last_zero));
            break;
        case 3:
            printf("%d", sum_before_and_after(arr, len_arr, first_zero, last_zero));
            break;
        default:
            puts(err_msg);
            break;
    }
}

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

    tasks(arr, len_arr, value);
}