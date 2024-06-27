#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int array[110];

int main() {
	int function, sizeOfArray = 0, currentSize = 0;
	scanf("%d", &function);
	while (getchar() != '\n') {
		scanf("%d", &array[currentSize]);
		++currentSize;
	}
	sizeOfArray = currentSize;
	switch (function) {
	case 0: printf("%d\n", max(array, sizeOfArray));
		break;
	case 1: printf("%d\n", min(array, sizeOfArray));
		break;
	case 2: printf("%d\n", diff(array, sizeOfArray));
		break;
	case 3: printf("%d\n", sum(array, sizeOfArray));
		break;
	default:
		printf("Данные некорректны\n");
	}
	return 0;
}
