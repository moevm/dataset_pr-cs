#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "sum_between_even_odd.h"

int main() {
    int k = 0, num, z;
    int arr[100];
    scanf("%i", &num);
    while (scanf("%i", &z) == 1) {
        arr[k] = z;
        k++;
    }
    switch (num) {
    case 0:
        printf("%i", index_first_even(arr,k));
        break;
    case 1:
        printf("%i", index_last_odd(arr,k));
        break;
    case 2:
        printf("%i", sum_between_even_odd(arr, k));
        break;
    case 3:
        printf("%i", sum_before_even_and_after_odd(arr, k));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
}
