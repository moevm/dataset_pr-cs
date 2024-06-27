#include "index_last_negative.h"

// индекс последнего отрицательного элемента
int index_last_negative(int array[], int size) {
    for (int i = size; i >= 0; i--) {
        if (array[i] < 0) {
            return i;
        }
    }
}
