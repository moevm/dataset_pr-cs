#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_before_even_and_after_odd.h"
int sum_before_even_and_after_odd(int mas[], int count) {
    int first_even = index_first_even(mas, count);
    int last_odd = index_last_odd(mas, count);
    int sm = 0;
    for (int ind = 0; ind < first_even; ind++) {
        sm += abs(mas[ind]);
    }
    for (int ind = last_odd; ind < count; ind++) {
        sm += abs(mas[ind]);
    }
    return sm;
}
