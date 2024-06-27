#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_before_and_after_negative.h"
#include "multi_between_negative.h"

int main() {
    int num = 20, n, size = 0;
    char c;
    int arr[num];
    scanf("%d", &n);
    c = getchar();
    for (int i = 0; i < num; i++) {
        if (c == '\n') {
            break;
        } else {
            scanf("%d", &arr[i]);
            c = getchar();
            size++;
        }
    }
    switch (n) {
        case 0:
            printf("%d\n", index_first_negative(arr, size));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, size));
            break;
        case 2:
            printf("%d\n", multi_between_negative(arr, size));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(arr, size));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}