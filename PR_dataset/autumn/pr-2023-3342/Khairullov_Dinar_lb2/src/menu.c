#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#include "console_input_opt.h"
#include "console_input_arr.h"
#include "final_result.h"

#define ARR_MAX_SIZE 20

int main(){
    int option = console_input_opt();
    int arrayy[ARR_MAX_SIZE];
    int number_of_array_elements = console_input_arr(arrayy);
    final_result(option, arrayy, number_of_array_elements);
    return 0;
}