#include"sum.h"

int sum(int* arr, int size) {
	int i = 0;
	int summa = 0;
	int mn;
	mn = min(arr, size);
	while (arr[i] != mn) {
		summa += arr[i];
		i++;
	}
	return summa;
}
