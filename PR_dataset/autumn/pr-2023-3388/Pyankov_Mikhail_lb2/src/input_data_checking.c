#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "input_data_checking.h"

int input_data_checking(int *array, int key, int length)
{
    if(index_first_negative(array, length)==-1||(index_first_negative(array, length)==index_last_negative(array, length)&&key>1))
    {
        printf("Данные некорректны");
        return 0;
    }
    return 1;
}
