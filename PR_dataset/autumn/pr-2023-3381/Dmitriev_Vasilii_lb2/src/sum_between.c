#include "sum_between.h"
#include "sum_elements.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_between(int array[], int len){
	int first = index_first_zero(array,len);
	int last = index_last_zero(array,len);
        return sum_elements(array,first,last);

}
