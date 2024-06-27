#include <stdlib.h>

int abs_max(int int_numbers[], int ct){
    int clear_number = 0;
    for(int i=0; i<ct; i++){
        if (abs(int_numbers[i]) > abs(clear_number)){
            clear_number = int_numbers[i];
        }
    }
    return clear_number;
}
