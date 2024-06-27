#include "choice.h"

int choice(int nums[], int size, int command){
    switch(command){
       case 0:
          printf(PRINT_NUM, index_first_negative(nums, size));
          break;
       case 1:
          printf(PRINT_NUM, index_last_negative(nums, size));
          break;
       case 2:
          sum_between_negative(nums, size);
          break;
       case 3:
          sum_before_and_after_negative(nums, size);
          break;
       default:
          printf("%s\n", OUTPUT_ERROR_STRING);
   }
}
