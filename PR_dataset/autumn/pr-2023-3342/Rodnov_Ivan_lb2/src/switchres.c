#include <stdio.h>
#include "switchres.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_after.h"
#define LNBREAK "%d\n"

void switchres(int num_func, int *arr, int n)
{
 switch (num_func)
    {
    case 0:
        printf(LNBREAK, index_first_zero(arr, n));
        break;
    case 1:
        printf(LNBREAK, index_last_zero(arr, n));
        break;
    case 2:
        printf(LNBREAK, sum_between(arr, n));
        break;
    case 3:
        printf(LNBREAK, sum_before_after(arr ,n));
        break;
    default:
        printf("%s\n", "Данные некорректны");
        break;
    }
}
