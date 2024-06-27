#include <stdio.h>
#include "abs_min.h"
#include "abs_max.h"
#include "diff.h"
#include "sum.h"
int oper(int * array, int input_length, int operation)
{
    switch(operation)
    {
        case 0:
        {
            printf("%d", abs_max(array, input_length));
            break;
        }
        case 1:
        {
            printf("%d", abs_min(array, input_length));
            break;
        }
        case 2:
        {
            printf("%d", abs_max(array, input_length) - abs_min(array, input_length));
            break;
        }
        case 3:
        {
            printf("%d", sum(array, input_length));
            break;
        }
        default:{
        printf("Данные некорректны");}
    }
    return 0;
}
