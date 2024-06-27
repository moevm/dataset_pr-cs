#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
int main() {
    char symbol;
    int command, count = 0;
    int arr_int[100];
    scanf("%d%c", &command, &symbol);
    while (symbol == ' ') {
        scanf("%d%c", &arr_int[count], &symbol);
        count++;
    }
    switch (command) {
        case 0: printf("%d\n", abs_max(arr_int, count));
                break;
        case 1: printf("%d\n", abs_min(arr_int, count));
                break;
        case 2: printf("%d\n", diff(arr_int, count));
                break;
        case 3: printf("%d\n", sum(arr_int, count));
                break;
        default: printf("Данные некорректны\n");
    }
    return 0;
}