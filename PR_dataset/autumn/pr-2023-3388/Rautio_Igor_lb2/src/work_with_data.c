#include <stdio.h>
#include "work_with_data.h"
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"
#define WORK(func) printf("%d\n", func(numbers, len));
void work_with_data(int option, int* numbers, int len) {
	switch (option) {
		case 0:
			WORK(findMax)
			break;
		case 1:
			WORK(findMin);
			break;
		case 2:
			WORK(findDiff);
			break;
		case 3:
			WORK(findSumBeforeMin);
			break;
		default:
			printf("Данные некорректны\n");
	}
}

