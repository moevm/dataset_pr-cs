#include "min.h"

int min(int array[], int index){
    int arrayMin = array[0];
    for (int i = 1; i < index; i++){
        if (array[i] < arrayMin){
            arrayMin = array[i];
        }
    }
    return arrayMin;
}
