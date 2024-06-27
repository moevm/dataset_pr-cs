#include "menu.h"

int main() {
	int operation, size = 0, arr[N], id_max, id_min;
	operation = input_operation();
	size = input_array(arr);
	answer(arr, size, operation, id_max, id_min);
}
