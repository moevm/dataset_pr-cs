#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"
#include "get_data.h"
#include "work_with_data.h"
#define MAX_ARRAY_LEN 100

int main() {
	int numbers[MAX_ARRAY_LEN] = {0}; 
	int len = 0;
	int option = get_data(numbers, &len);
	if (option == -1) return 1;

	work_with_data(option, numbers, len);

	return 0;
}
