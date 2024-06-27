#include <stdio.h>
#include <limits.h>

int array[110];

int max(int array[], int sizeOfArray) {
	int maximum = 0;
	for (int i = 0; i < sizeOfArray; ++i) {
		if (array[i] > maximum)
			maximum = array[i];
	}
	return maximum;
}

int min(int array[], int sizeOfArray) {
	int minimum = INT_MAX;
	for (int i = 0; i < sizeOfArray; ++i) {
		if (array[i] < minimum)
			minimum = array[i];
	}
	return minimum;
}

int diff(int array[], int sizeOfArray) {
	return max(array, sizeOfArray) - min(array, sizeOfArray);
}

int sum(int array[], int sizeOfArray) {
	int sum = 0;
	int minimum = min(array, sizeOfArray);
	for (int i = 0; i < sizeOfArray; ++i) {
		if (minimum != array[i])
			sum += array[i];
		else
			break;
	}
	return sum;
}

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