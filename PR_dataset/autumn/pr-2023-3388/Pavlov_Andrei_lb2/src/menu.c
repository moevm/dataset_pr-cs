#include "io_routine.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#define MAX_INPUT_LEN 100

void process_data(int command, int* array, unsigned int length) {
    switch (command) {
        case 0:
            answer(index_first_zero(array, length));
            break;
        case 1:
            answer(index_last_zero(array, length));
            break;
        case 2:
            answer(sum_between(array, length));
            break;
        case 3:
            answer(sum_before_and_after(array, length));
            break;
        default:
            error();
     }
     return;
}


int main() {
    int data[MAX_INPUT_LEN] = { 0 };
    unsigned int data_length = 0;
    int command = get_data(data, &data_length);
    process_data(command, data, data_length);
    return 0;
}
