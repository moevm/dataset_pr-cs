#include "index_first_negative.h"
#include "index_last_negative.h"

long long int multi_between_negative(int * array, int len_array) {
    int i;
    long long int multi = 1;
    int start = index_first_negative(array, len_array);
    int finish = index_last_negative(array, len_array);
    for (i = start; i < finish; i ++) {
        multi *= array[i];
    }
    return multi;
}
