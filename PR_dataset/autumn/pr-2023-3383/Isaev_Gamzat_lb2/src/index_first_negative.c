#include "index_first_negative.h"
int index_first_negative(int mas[], int count) {
    for (int i = 0; i < count; i++) {
        if (mas[i] < 0) {
            return i;
        }
    }
}
