#include "index_last_zero.h"
#include "search_index_zero.h"

int index_last_zero(int array[], int len){
	 return search_index_zero(array, len-1, -1, -1);

}
