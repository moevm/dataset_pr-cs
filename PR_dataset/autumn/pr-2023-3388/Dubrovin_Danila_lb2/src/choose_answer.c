#include "choose_answer.h"
#include "max.h"
#include "min.h"
#include "show_answer.h"
#include "diff.h"
#include "sum.h"

void choose_answer(int value, int array[], int length)
{
    switch (value)
    {
    case 0:
        show_answer(get_max(array,length));
        break;
    case 1:
        show_answer(get_min(array,length));
        break;
    case 2:
        show_answer(get_diff(array,length));
        break;
    case 3:
        show_answer(get_sum(get_min(array,length),array));
        break;
    default:
        show_answer(INT_MIN);
        break;
    }
}
