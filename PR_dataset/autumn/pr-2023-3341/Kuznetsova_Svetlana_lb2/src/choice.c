#include "choice.h"
#define out "%d\n"

int choice(int arr[], int size, int key) {
	switch (key) {
	case 0:
		printf(out, max(arr, size));
		break;
	case 1:
		printf(out, min(arr, size));
		break;
	case 2:
		printf(out, diff(arr, size));
		break;
	case 3:
		printf(out, sum(arr, size));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
}

