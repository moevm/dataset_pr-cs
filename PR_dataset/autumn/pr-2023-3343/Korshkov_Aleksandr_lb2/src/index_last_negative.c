#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "index_last_negative.h"

int index_last_negative(int arr[20], int m) { 
    int last_index = -1; 
    for (int i = 0; i < 20; i++) {
        if (arr[i] < 0) {
            last_index = i;
        }
    }

    if (last_index != -1) {
        if (m == 1) {
            printf("%d", last_index);
        }
        return last_index;
    }
    else {
        printf("Данные некорректны");
        exit(0);
    }
    
}