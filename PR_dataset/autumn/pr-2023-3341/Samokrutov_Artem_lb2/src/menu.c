#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

#define SIZE_TMP 2048
#define MAX_LENGTH 100
#define OUT "%d\n"


void input(char tmp[], char *command)
{
	fgets(tmp, SIZE_TMP, stdin);
	*command = tmp[0];
		if (tmp[1] != ' ') {
	       *command = '?';
	}
}

void fill_array(char tmp[], int arr[], int *length)
{
	char *substr;
	substr = strtok(tmp, " ");
	substr = strtok(NULL, " ");

	while (substr != NULL) {
		arr[(*length)++] = atoi(substr);
		substr = strtok(NULL, " ");
	}
}

void case_choice(char command, int arr[], int length)
{
	switch(command) {
	case '0': 
	{
		printf(OUT, index_first_negative(arr, length));
		break;
	}
	case '1':
	{
		printf(OUT, index_last_negative(arr, length));
		break;
	}
	case '2':
	{
		printf(OUT, sum_between_negative(arr, length));
		break;
	}
	case '3':
	{
		printf(OUT, sum_before_and_after_negative(arr, length));
		break;
	}
	default:
	{
		printf("Данные некорректны\n");
	}
	}

}

int main()
{
	char tmp[SIZE_TMP];
	char command;
	int arr[MAX_LENGTH];
	int length = 0;

	input(tmp, &command);
	fill_array(tmp, arr, &length);
	case_choice(command, arr, length);

	return 0;
}
