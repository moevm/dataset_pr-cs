#include <stdio.h>

int max(int array[100], int len){
    int max = array[0];
    for (int i = 0; i < len; i++){
        if (array[i] > max){
            max = array[i];
        }
    }
    return max;
}
