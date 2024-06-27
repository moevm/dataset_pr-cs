#include"index_last_negative.h"

int index_last_negative(int array[], int array_size)
{
   for (int i = array_size; i > 0; i --)
   {
      if (array[i] < 0)
      {
	 return i;
      }
   }
   return 0;
}
