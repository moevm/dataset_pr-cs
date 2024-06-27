#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

#define MAX_SIZE 100

int main() {
	int mode;
	int arr[MAX_SIZE] = {};
	int size = 0;
	char end;

	scanf("%d%c", &mode, &end);
     	for (int i = 0; i < MAX_SIZE; i++) {
		scanf("%d%c", &arr[i], &end);
		size++;
		if (end == '\n') {
			break;
		}
	}

	switch (mode) {
		case 0:
			printf("%d\n", max(arr, size));
			break;

		case 1:
			printf("%d\n", min(arr, size));
			break;

		case 2:
			printf("%d\n", diff(arr, size));
			break;

		case 3:
			printf("%d\n", sum(arr, size));
			break;

		default:
			printf("Данные некорректны\n");
			return 1;
	}
	return 0;
}
