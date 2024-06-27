#include"multi_before_and_after_negative.h"
#include"index_first_negative.h"
#include"index_last_negative.h"

int multi_before_and_after_negative(int array[], int array_size)
{
   int multi_result = 1;
   int start = index_last_negative(array, array_size);
   int end = index_first_negative(array,array_size);
   for (int i = 0; i < end; i ++)
   {
      multi_result *= array[i];
   }
   for (int i = start; i < array_size; i ++)
   {
      multi_result *= array[i];
   }
   if (multi_result == 1) 
   {
      return 0;
   }
   else
   {
      return multi_result;
   }
}

