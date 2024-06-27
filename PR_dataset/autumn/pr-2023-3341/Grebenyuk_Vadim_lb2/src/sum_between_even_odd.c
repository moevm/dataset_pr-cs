#include "sum_between_even_odd.h"

#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum.h"

int sum_between_even_odd() {
    return sum(index_first_even(), index_last_odd());
}