#include "Func_index_last_odd.h"
int Func_index_last_odd(int* massive_int, int count_number_massive) {
	int index_iterator = count_number_massive;
	while (index_iterator > 0) {
		if (massive_int[index_iterator] % 2 != 0) {
			return index_iterator;
		}
		else {
			index_iterator--;
		}
	}
	return index_iterator;
}