#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

#define MAX_LENGHT 100
#define ANSWER "%d\n"

void execFun(){
	switch (input)
	{
	case 0:
		printf(ANSWER, max(array, size_array));
		break;
	case 1:
		printf(ANSWER, min(array, size_array));
		break;
	case 2:
		printf(ANSWER, diff(array, size_array));
		break;
	case 3:
		printf(ANSWER, sum(array, size_array));
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

int main(){
	int array[MAX_LENGHT];
	int input;
	int size_array = 0;
	char space = ' ';
	scanf("%d", &input);
	enterArray();
	execFun();
}