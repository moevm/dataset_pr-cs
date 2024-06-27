#include "index_first_zero.h"
#include "search_index_zero.h"

int index_first_zero(int array[],int len){
         return search_index_zero(array, 0, len, 1);
}
