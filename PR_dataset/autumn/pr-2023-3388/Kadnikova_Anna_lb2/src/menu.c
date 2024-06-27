#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#include "switchfunc.h"
#define ERR -1
#define OUTPUT_ERR "Данные некорректны"

#define N 100
int main(void) {
    int chisla = inputfunc();
    int variant = 0;
    scanf("%d", &variant);
    switchfunc(variant);
    return 0;
}
