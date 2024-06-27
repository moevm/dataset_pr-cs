#include <stdio.h>
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int main() {
    int action;
    int arr[20];
    int len = 0;
    scanf("%d", &action);
    do {
        scanf("%d", &arr[len]);
        len++;
    } while (getchar() != '\n');
    switch (action) {
        case 0:
            if (index_first_negative(arr, len) == -1) {
                printf("Данные некорректны\n");
            } else
                printf("%d\n", index_first_negative(arr, len));
            break;
        case 1:
            if (index_last_negative(arr, len) == -1) {
                printf("Данные некорректны\n");
            } else
                printf("%d\n", index_last_negative(arr, len));
            break;
        case 2:
            if (index_first_negative(arr, len) == -1 || index_last_negative(arr, len) == -1) {
                printf("Данные некорректны\n");
            } else
                printf("%d\n", multi_between_negative(arr, len));
            break;
        case 3:
            if (index_first_negative(arr, len) == -1 || index_last_negative(arr, len) == -1) {
                printf("Данные некорректны\n");
            } else
                printf("%d\n", multi_before_and_after_negative(arr, len));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}