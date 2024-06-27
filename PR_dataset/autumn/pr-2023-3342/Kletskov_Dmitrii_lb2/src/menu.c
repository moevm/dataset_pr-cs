#include <stdio.h>
#include "diff.h"
#include "max.h"
#include "min.h"
#include "sum.h"

#define OUTPUTSTRING "%d\n"
#define SIZE 100

void answer();

int main() {
    answer();
    return 0;
}

void answer() {
    int choice;
    int arr[SIZE];
    int size;

    // Ввод значения choice (0, 1, 2 или 3)
    scanf("%d", &choice);
    input(arr, &size);
    switch (choice) {
        case 0:
            printf(OUTPUTSTRING, max(arr, size));
            break;
        case 1:
            printf(OUTPUTSTRING, min(arr, size));
            break;
        case 2:
            printf(OUTPUTSTRING, diff(arr, size));
            break;
        case 3:
            printf(OUTPUTSTRING, sum(arr, size));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}

int input(int arr[], int *size) {
    *size = -1;
    while ((*size) < 99 && scanf("%d", &arr[++(*size)]) == 1);
    return 0;  // Добавим возвращаемое значение
}
