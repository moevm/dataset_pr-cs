#include "abs_max.h"

int abs_max(int array_num[], int length) {
    int max_num = 0;
    int answer = 0;

        for (int i = 0; i < length; i++) {
        if(abs(array_num[i]) > max_num ){
            max_num = abs(array_num[i]);
            answer = array_num[i];
        }
    }
    return answer;
}