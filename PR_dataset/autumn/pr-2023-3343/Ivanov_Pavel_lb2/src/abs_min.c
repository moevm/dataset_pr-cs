#include <stdlib.h>

int abs_min(int int_numbers[], int ct){
    int mnabs = 2147483647;
    for(int i=0; i<ct; i++){
        if (abs(int_numbers[i]) < abs(mnabs)){
            mnabs = int_numbers[i];
        }
    }
    return mnabs;
}