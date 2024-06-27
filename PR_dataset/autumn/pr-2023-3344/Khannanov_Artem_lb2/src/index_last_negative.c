#include "index_last_negative.h"

int index_last_negative(int array[], int len_array) {
    int ret_value;

    for (int i = len_array - 1; i >= 0; i--) {

        if (array[i] < 0) {
            ret_value = i;
            break;}
    }
    return ret_value;
}