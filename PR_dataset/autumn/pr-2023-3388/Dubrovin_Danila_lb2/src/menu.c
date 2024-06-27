#include <stdio.h>
#include <limits.h>
#include "read_array.h"
#include "choose_answer.h"
#define ARRAY_LENGTH 100

int main()
{
    int array[ARRAY_LENGTH];
    int value = 0, length = 0;
    read_array(array,&value,&length);
    choose_answer(value, array, length);
    return 0;
}
