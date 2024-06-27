
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_text.h"

int words_three_symbols(char* str) {
	int count = 0;
	char* istr = malloc(strlen(str) * sizeof(char));
	if (istr == NULL) {
		printf("ERROR: Memory allocation error.\n");
		exit(1);
	}
	strcpy(istr, str);
	istr = strtok(istr, " \n\t.,");
	while (istr != NULL)
	{
		if (strlen(istr) == 3)
			count += 1;
		istr = strtok(NULL, " \n\t.,");
	}
	return count;

}

int cmp(const void* a, const void* b) {
	char* str1 = *(char**)a;
	char* str2 = *(char**)b;
	int count_a = words_three_symbols(*(char**)a);
	int count_b = words_three_symbols(*(char**)b);
	return count_a < count_b
		? 1
		: count_a > count_b
		? -1
		: 0;
}

void func4(char** text, int num_str) {
	qsort(text, num_str, sizeof(char*), cmp);
}
