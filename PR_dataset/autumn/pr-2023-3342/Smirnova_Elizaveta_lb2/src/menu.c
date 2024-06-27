#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#include "input.h"
#include "output.h"
#define N 100
#define print_str "%d\n"

int main()
{
    int numbers[N];
    int size = 0, sign;

    scanf("%d", &sign);

    size = input (numbers);

    output(sign, numbers, size);

    return 0;
}
