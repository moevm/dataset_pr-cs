#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int sum_before_and_after(int len_a ,int a[]) {
    int sum_array = 0;
    int index_last_funct = index_last_zero(len_a, a);
    int index_first_funct = index_first_zero(len_a, a);
    if ((index_last_funct == -1) || (index_first_funct == -1))
        return -1;
    else {
        for (int i = 0; i < index_first_funct; i++)
            sum_array += abs(a[i]);
        for (; index_last_funct < len_a; index_last_funct++)
            sum_array += abs(a[index_last_funct]);
        return sum_array;
    }
}