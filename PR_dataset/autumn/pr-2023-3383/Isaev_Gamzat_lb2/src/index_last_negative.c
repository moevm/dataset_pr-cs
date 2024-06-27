#include "index_last_negative.h"
int index_last_negative(int mas[], int count) {
    for (int i = count - 1; i >= 0; i--) {
        if (mas[i] < 0) {
            return i;
        }
    }
}
