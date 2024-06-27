#include "output.h"
void output(int *arr, int size, int task){
	int ans = 0;
	switch(task){
		case 0:
			ans = index_first_negative(arr, size);
			break;
		case 1:
			ans = index_last_negative(arr, size);
			break;
		case 2:
			ans = sum_between_negative(arr, size);
			break;
		case 3:
			ans = sum_before_and_after_negative(arr, size);
			break;
		default:
			printf("Данные некорректны\n");
			return;
	}
	printf("%d\n", ans);
}
