#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
#define LEN 100

int main()
{
    int action;
    scanf("%d", &action);

    int int_numbers[LEN];
    int ct = 0;
    while (getchar() != '\n'){
        scanf("%d", &int_numbers[ct]);
        ct++;
    }

    switch (action){
        case 0:
            printf("%d\n", abs_max(int_numbers, ct));
            break;
        case 1:
            printf("%d\n", abs_min(int_numbers, ct));
            break;
        case 2:
            printf("%d\n", diff(int_numbers, ct));
            break;
        case 3:
            printf("%d\n", sum(int_numbers, ct));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }

    return 0;
}
