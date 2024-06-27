#include "sum_before_even_and_after_odd.h"
#include "Func_index_first_even.h"
#include "Func_index_last_odd.h"
#include <stdlib.h>
int sum_before_even_and_after_odd(int* massive, int count_number_massive) {
	int iterator = 0;
	int summ_abs_first = 0;
	int summ_abs_second = 0;
	int number_fisrt_even = Func_index_first_even(massive,count_number_massive);
	int number_last_odd = Func_index_last_odd(massive, count_number_massive);
	for (iterator;iterator < number_fisrt_even ;iterator++)
	{
		summ_abs_first+= abs(massive[iterator]);
	}
	for (int iterator2 = count_number_massive;iterator2 != number_last_odd-1;iterator2--){
		summ_abs_second+= abs(massive[iterator2]);
	}
	return summ_abs_first + summ_abs_second;
}