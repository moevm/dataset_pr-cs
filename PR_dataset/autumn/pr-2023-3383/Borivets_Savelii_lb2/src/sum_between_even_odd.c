#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
int sum_between_even_odd(int mas[], int count) {
    int first_even = index_first_even(mas, count);
    int last_odd = index_last_odd(mas, count);
    int sm = 0;
    for (int ind = first_even; ind < last_odd; ind++) {
        sm += abs(mas[ind]);
    }
    return sm;
}
