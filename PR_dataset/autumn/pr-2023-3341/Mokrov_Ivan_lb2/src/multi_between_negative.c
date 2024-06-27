#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

// Найти произведение элементов массива, расположенных от первого отрицательного элемента  и до последнего отрицательного
int multi_between_negative(int array[], int size) {
    int first = index_first_negative(array, size);
    int last = index_last_negative(array, size);

    int return_index = 1;

    for (int i = first; i < last; i++) {
        return_index *= array[i];
    }
    return return_index;
}
