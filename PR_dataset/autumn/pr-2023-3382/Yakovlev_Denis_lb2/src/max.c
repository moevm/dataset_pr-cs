#include "max.h"

int max(int array[], int length) {
    int answer = 0;
    for (int j = 0; j < length; j++) {
        if (array[j] > answer) {
            answer = array[j];
        }
    }
    return answer;
}