#include "index_last_negative.h"

int index_last_negative(int arr[], int size) {
    int answer;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            answer = i;
        }
    }
    return answer;
}