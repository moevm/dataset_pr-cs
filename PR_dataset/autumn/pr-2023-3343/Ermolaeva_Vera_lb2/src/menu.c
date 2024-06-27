#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

int main() {
    int option;
    int numbers[20];

    int size = 0;
    scanf("%d", &option);

    while (getchar() != '\n') {
        scanf("%d", &numbers[size]);
        size++;
    }

    switch (option) {
        case 0:
            printf("%d\n", index_first_negative(numbers, size));
            break;
        case 1:
            printf("%d\n", index_last_negative(numbers, size));
            break;
        case 2:
            printf("%d\n", multi_between_negative(numbers, size));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(numbers, size));
            break;
        default:
            printf("%s\n", "Данные некорректны");
    }

    return 0;
}