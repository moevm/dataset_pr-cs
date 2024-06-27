#include "Libraries.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

#define RESULT "%d\n"

void output(int funcType, int size, int array[])
{
    switch (funcType)
    {
        case(0):
            printf(RESULT, index_first_negative(size, array));
            break;
        case(1):
            printf(RESULT, index_last_negative(size, array));
            break;
        case(2):
            printf(RESULT, sum_between_negative(size, array));
            break;
        case(3):
            printf(RESULT, sum_before_and_after_negative(size, array));
            break;
        default:
            printf("Данные некорректны\n");
    }
}