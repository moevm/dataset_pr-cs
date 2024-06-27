#include "sum_between_even_odd.h"
#include "Func_index_first_even.h"
#include "Func_index_last_odd.h"
#include <stdlib.h>
int sum_between_evenodd(int* massive, int count_number_massive) {
	int iterator = Func_index_first_even(massive,count_number_massive);
	int summ_abs = 0;
	for (iterator; iterator < Func_index_last_odd(massive,count_number_massive); iterator++) {
		summ_abs = abs(massive[iterator]) + summ_abs;
	}
	return summ_abs;

}