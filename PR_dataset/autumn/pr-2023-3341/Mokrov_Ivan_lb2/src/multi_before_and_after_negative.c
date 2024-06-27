#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

// Найти произведение элементов массива, расположенных до первого отрицательного элемента и после последнего отрицательного
int multi_before_and_after_negative(int array[], int size) {
    int first = index_first_negative(array, size);
    int last = index_last_negative(array, size);

    int return_index = 1;

    for (int i = 0; i < first; i++) {
        return_index *= array[i];
    }
    for (int i = last; i < size; i++) {
        return_index *= array[i];
    }
    return return_index;
}
