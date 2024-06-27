#include<stdio.h>
#include"sum.h"

int main() {
	int command;
	int size = 0;
	int arr[100];
	scanf("%d", &command);
	do {
		scanf("%d", &arr[size++]);
	} while (getchar() != '\n');
	switch (command) {
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
		break;
	}
	return 0;
}
