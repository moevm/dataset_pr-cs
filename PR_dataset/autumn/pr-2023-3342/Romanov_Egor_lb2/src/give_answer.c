#include "give_answer.h"
#define PRINT_NUM %d\n
void give_answer() {
    int nums[NUMS_ARR_LENGTH];
    int array_length = 0;
    int program_mode = get_data(nums, &array_length);
    switch (program_mode) {
        case(0):
            printf("PRINT_NUM", index_first_even(nums, array_length));
            break;
        case(1):
            printf("PRINT_NUM", index_last_odd(nums, array_length));
            break;
        case(2):
            printf("PRINT_NUM", sum_between_even_odd(nums, array_length));
            break;
        case(3):
            printf("PRINT_NUM", sum_before_even_and_after_odd(nums, array_length));
            break;
        default:
            printf("PRINT_NUM", "Данные некорректны");
    }
}
