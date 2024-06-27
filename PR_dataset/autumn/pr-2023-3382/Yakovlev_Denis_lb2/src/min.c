#include "min.h"

int min(int array[], int length) {
    int answer = 10000000;
    for (int j = 0; j < length; j++) {
        if (array[j] < answer) {
            answer = array[j];
        }
    }
    return answer;
}