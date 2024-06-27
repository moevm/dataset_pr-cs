#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main() {
	int size, mode, num[100];
	size = 0;
	char cur_c = ' ';
	scanf("%d", &mode);

	for (int i = 0; cur_c != '\n'; i++) {
		scanf("%d%c", &num[i], &cur_c);
		size = i + 1;
	}

	switch(mode) {
		case 0:
			printf("%d", abs_max(num, size));
		break;
		case 1:
			printf("%d", abs_min(num, size));
		break;
		case 2:
			printf("%d", diff(num, size));
		break;
		case 3:
			printf("%d", sum(num, size));
		break;
		default:
			printf("Данные некорректны");
		break;
	}

	return 0;
}