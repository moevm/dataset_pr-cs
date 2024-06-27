#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main() {
    int a;
    scanf("%d", &a);
    int len = 0;
    int arr[100];
    char g;
    while (len < 100) {
        scanf("%d%c", &arr[len], &g);
        if (g == '\n') {
            len++;
            break;
        } else {
            len++;
        }
    }

    switch (a) {
        case 0:
            printf("%d\n", abs_max(arr, len));
            break;
        case 1:
            printf("%d\n", abs_min(arr, len));
            break;
        case 2:
            printf("%d\n", diff(arr, len));
            break;
        case 3:
            printf("%d\n", sum(arr, len));
            break;
        default:
            printf("Данные некорректны\n");
    }

    return 0;
}