#include "sum.h"
#include "min.h"

int sum(int array[], int index){
    int sumToMin = 0;
    int minInArray = min(array, index);
    int indexCounter = 0;
    while (array[indexCounter] != minInArray){
        sumToMin += array[indexCounter];
        indexCounter++;
    }
    return sumToMin;
}
