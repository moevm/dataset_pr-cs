#include <stdio.h>

int min(int array[100], int len){
    int min = array[0];
    for (int i = 0; i < len; i++){
        if (array[i] < min){
            min = array[i];
        }
    }
    return min;
}
