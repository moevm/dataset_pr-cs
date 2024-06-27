#include "index_first_negative.h"
#include "index_last_negative.h"

long long int multi_before_and_after_negative(int * array, int len_array) {
    int i;
    long long int multi = 1;
    int finish = index_first_negative(array, len_array);
    int start = index_last_negative(array, len_array);
    for (i = 0; i < finish; i ++) {
        multi *= array[i];
    }
    for (i = start; i < len_array; i ++) {
        multi *= array[i];
    }
    return multi;
}
