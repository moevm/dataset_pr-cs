#include "index_last_odd.h"
int index_last_odd(int arr[], int array_length) {
    int last_ind = 0;

    for (int i = 0; i < array_length; i++) {
        if (abs(arr[i]) % 2 == 1) {
            last_ind = i;

        }
    }
    return last_ind;
}
