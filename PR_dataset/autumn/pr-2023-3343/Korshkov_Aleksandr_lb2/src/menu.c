#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_before_and_after_negative.h"
#include "multi_between_negative.h"

int main() {
    setlocale(LC_ALL, "Rus");

    int arr[20], n, i = 0;
    for (i; i < 20; i++) {
        arr[i] = 0;
    }

    i = 0;
    scanf("%d", &n); 
    do {
        scanf("%d", &arr[i]); 
        i++;
    }
    while (getchar() != '\n');

    switch (n) {
    case 0:
        index_first_negative(arr, 1);
        break;
    case 1:
        index_last_negative(arr, 1);
        break;
    case 2:
        multi_between_negative(arr);
        break;
    case 3:
        multi_before_and_after_negative(arr, i); 
        break;
    default:
        printf("Данные некорректны");
        break;
    }

    return 0;
}