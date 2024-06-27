#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#include "choice.h"
#include "input_command.h"
#include "input_data.h"

int main(){
   int command, size, nums[MAX_ARRAY_SIZE];
   command = input_command();
   size = input_data(nums);
   choice(nums, size, command);
}
