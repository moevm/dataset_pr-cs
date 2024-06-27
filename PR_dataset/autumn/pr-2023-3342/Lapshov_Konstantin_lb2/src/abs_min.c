#include "abs_min.h"

int abs_min(int array_num[], int length) {
    int answer = array_num[0];
    int min_num = abs(array_num[0]);

    for (int i = 0; i < length; i++) {
        if (abs(array_num[i]) < min_num) {
            min_num = abs(array_num[i]);
            answer = array_num[i];
        }
    }
    return answer;
}