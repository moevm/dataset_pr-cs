#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
void answer(int znach, int array[], int length){
        switch(znach){
        case 0:
            printf("print_str",abs_max(array, length));
            break;
        case 1:
            printf("print_str",abs_min(array, length));
            break;
        case 2:
            printf("print_str",diff(array, length));
            break;
        case 3:
            printf("print_str",sum(array, length));
            break;
        default:
            printf("%s\n", "Данные некорректны");
    }
}
