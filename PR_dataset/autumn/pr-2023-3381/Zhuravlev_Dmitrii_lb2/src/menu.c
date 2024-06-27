#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
#include <stdio.h>

int main() {
	int instruction;
	scanf("%d", &instruction);

	int input_array[100] = {};
	char after_number;
	int lenght = 0;
	while ((after_number != '\n') && (lenght < 100)) {
		scanf("%d", &input_array[lenght]);
		lenght++;
		after_number = getchar();
	}

	switch (instruction) {
		case 0:
			printf("%d\n", input_array[abs_max(input_array, lenght)]);
			break;
		case 1:
			printf("%d\n", input_array[abs_min(input_array, lenght)]);
			break;
		case 2:
			printf("%d\n", diff(input_array, lenght));
			break;
		case 3:
			printf("%d\n", sum(input_array, lenght));
			break;
		default:
			printf("Данные некорректны\n");
	}	
}