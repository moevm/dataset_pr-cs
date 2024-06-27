#include "sum_before_and_after.h"
#include "sum_elements.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int array[], int len){
	 int one_summ = sum_elements(array,0,index_first_zero(array,len));
	 int two_summ = sum_elements(array,index_last_zero(array,len),len);

         return one_summ+two_summ;

}




