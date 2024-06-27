#include "sum_before_even_and_after_odd.h"

#include "global.h"
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum.h"

int sum_before_even_and_after_odd() {
    return sum(0, index_first_even()) + sum(index_last_odd(), length);
}