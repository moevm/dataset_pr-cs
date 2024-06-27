include "diff.h"
#include "abs_max.h"
#include "abs_min.h"
int diff(int array[], int length)
{
   return abs_max(array, length) - abs_min(array, length);

}