#include "index_last_negative.h"

//функция для значения 1
int index_last_negative(int arr[], int len) {
        for (int i = len; i >= 0; i--) {
                if (arr[i]<0) {
                        return i;
                }
        }
}

