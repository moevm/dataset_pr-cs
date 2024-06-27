#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "index_first_negative.h"

int index_first_negative(int arr[20], int m) {
    for (int i = 0; i < 20; i++) {
        if (arr[i] < 0) {
            if (m == 1) {
                printf("%d", i);
            }
            return i; 
        }
    }

    printf("Данные некорректны");
    exit(0);
}