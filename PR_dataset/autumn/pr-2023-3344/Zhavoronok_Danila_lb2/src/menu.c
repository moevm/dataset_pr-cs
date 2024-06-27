#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "sum_between_even_odd.h"
#include "enter_array_values.h"

int main()
{
    int mode = -1;
    scanf("%d", &mode);

    int array[100] = {0};
    int array_length = enter_array_values(array);

    int result = -1;
    switch (mode)
    {
    case 0:
        result = index_first_even(array, array_length);
        break;

    case 1:
        result = index_last_odd(array, array_length);
        break;

    case 2:
        result = sum_between_even_odd(array, array_length);
        break;

    case 3:
        result = sum_before_even_and_after_odd(array, array_length);
        break;

    default:
        printf("Данные некорректны\n");
        return 0;
    }

    printf("%d\n", result);
    return 0;
}
