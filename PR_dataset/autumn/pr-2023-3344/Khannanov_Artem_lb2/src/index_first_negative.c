#include "index_first_negative.h"


int index_first_negative(int array[], int len_array) {
    int ret_value;

    for (int i = 0; i < len_array; i++) {

        if (array[i] < 0) {
            ret_value = i;
            break;}
    }
    return ret_value;
}