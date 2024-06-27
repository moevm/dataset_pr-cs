#include <stdio.h>

int index_last_negative(int array[], int array_lenght) {
    int i = 0;
    int last_index = -1;
    for (i = 0;i < array_lenght;i++) {
        if (array[i] < 0) {
            last_index = i;
        }    
    }
    return last_index;
}    
