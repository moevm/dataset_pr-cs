#include "diff.h"
#include "max.h"
#include "min.h"

int get_diff(int array[], int length)
{
    return get_max(array,length) - get_min(array,length);
}
