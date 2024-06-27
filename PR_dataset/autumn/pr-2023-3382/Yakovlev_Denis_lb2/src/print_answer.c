#include "print_answer.h"
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

void print_answer(int number, int array[], int length) {
    switch (number) {
    case 0:
        printf("\n%d\n", max(array, length));
        break;
    case 1:
        printf("%d\n", min(array, length));
        break;
    case 2:
        printf("%d\n", diff(array, length));
        break;
    case 3:
        printf("%d\n", sum(array, length));
        break;
    default:
        printf("Данные некорректны\n");
    }
}