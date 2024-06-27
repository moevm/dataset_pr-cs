#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"`
#define N 100


int main() {
	int arr[N];
	int size = 0;
	int value;
	scanf("%d", &value);
	while (getchar() != '\n') {
		scanf("%d", &arr[size]);
		size = size + 1;
	}

	switch (value) {
	case 0:
		printf("%d\n", index_first_negative(arr, size));
		break;
	case 1:
		printf("%d\n", index_last_negative(arr, size));
		break;
	case 2:
		printf("%d\n", sum_between_negative(arr, size));
		break;
	case 3:
		printf("%d\n", sum_before_and_after_negative(arr, size));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
	return 0;
}
