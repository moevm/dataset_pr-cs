#include "abs_max.h"
#include "abs_min.h"

int diff(int int_numbers[], int ct){
    return (abs_max(int_numbers, ct) - abs_min(int_numbers, ct));
}