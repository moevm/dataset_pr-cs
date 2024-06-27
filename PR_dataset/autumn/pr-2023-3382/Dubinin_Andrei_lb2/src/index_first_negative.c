#include <stdio.h>

int index_first_negative(int array[],int array_lenght) {
    int i = 0;
    for (i = 0;i < array_lenght;i++) {
        if (array[i] < 0) {
            return i;
        }    
    }
        return -1;
}