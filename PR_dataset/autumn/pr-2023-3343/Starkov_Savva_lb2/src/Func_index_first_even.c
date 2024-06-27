#include "Func_index_first_even.h"
int Func_index_first_even(int* massive_int, int count_number_massive)
{
	int index_iterator = 0;
	while (index_iterator < count_number_massive) {
		if (massive_int[index_iterator] % 2 == 0) {
			return index_iterator;
		}
		else {
			index_iterator++;
		}
	}

}