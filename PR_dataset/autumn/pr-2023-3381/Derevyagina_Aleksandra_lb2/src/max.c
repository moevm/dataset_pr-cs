#include "max.h"

int max(int array[], int index){
    int arrayMax = array[0];
    for (int i = 1; i < index; i++){
        if (array[i] > arrayMax){
            arrayMax = array[i];
        }
    }
    return arrayMax;
}
