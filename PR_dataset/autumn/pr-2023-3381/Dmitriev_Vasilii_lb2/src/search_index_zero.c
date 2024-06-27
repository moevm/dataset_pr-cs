#include "search_index_zero.h"
//общая функция по поиску индекса нуля
int search_index_zero(int array[], int start, int end, int step){
         for(int i=start;i!=end;i+=step){
                 if (array[i] == 0){
                          return i;
                  }

         }

         return -1;
	
}

