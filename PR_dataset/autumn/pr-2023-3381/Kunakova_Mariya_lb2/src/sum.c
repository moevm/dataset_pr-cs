#include "sum.h"

int sum(int arr[], int len_arr) {
	int flag = 0;
	int max = abs_max(arr, len_arr);
	int summa = 0;
	for (int i = 0; i < len_arr; i++) {
		if (arr[i] == max) {
			flag = 1;
		}
		if (flag == 1) {
			summa += arr[i];
		}
	}
	return summa;
}
