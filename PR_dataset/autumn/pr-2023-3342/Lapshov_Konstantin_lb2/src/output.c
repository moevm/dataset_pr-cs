#include "output.h"
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

#define STRING "%d\n"

void output(int choice, int array[], int array_length){
    switch (choice) {
        case 0:
            printf(STRING, abs_max(array, array_length));
            break;
        case 1:
            printf(STRING, abs_min(array, array_length));
            break;
        case 2:
            printf(STRING, diff(array, array_length));
            break;
        case 3:
            printf(STRING, sum(array, array_length));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}