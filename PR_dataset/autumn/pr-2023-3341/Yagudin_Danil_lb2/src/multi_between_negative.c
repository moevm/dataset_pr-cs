#include"multi_between_negative.h"
#include"index_first_negative.h"
#include"index_last_negative.h"

int multi_between_negative(int array[], int array_size)
{
   int multi_result = 1;
   int start = index_first_negative(array, array_size);
   int end = index_last_negative(array, array_size);
   for (int i = start; i < end; i ++)
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
