#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

#define MAX_LENGHT 100
#define RESULT "%d\n"

void execFun(){
	switch (input)
	{
	case 0:
		printf(RESULT, abs_max(array, size_array));
		break;
	case 1:
		printf(RESULT, abs_min(array, size_array));
		break;
	case 2:
		printf(RESULT, diff(array, size_array));
		break;
	case 3:
		printf(RESULT, sum(array, size_array));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
}

void enterArray(){
	while (size_array < MAX_LENGHT && space == ' ') {
		scanf("%d%c", &array[size_array], &space);
		size_array++;
	}
}

int main() {
	int array[MAX_LENGHT];
	int input;
	int size_array = 0;
	char space = ' ';
	scanf("%d", &input);
	enterArray();
	execFun();
}
