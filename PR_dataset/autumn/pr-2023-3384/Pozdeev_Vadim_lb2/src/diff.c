#include "abs_max.h"
#include "abs_min.h"
int diff(int * array, int input_length){
        return abs_max(array, input_length)  - abs_min(array, input_length);
}
