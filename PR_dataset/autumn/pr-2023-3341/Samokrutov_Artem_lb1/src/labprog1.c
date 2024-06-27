#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_TMP 2048
#define MAX_LENGTH 100


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

int index_first_negative(int arr[], int length) 
{
	for (int i = 0; i < length; i++) {
		if (arr[i] < 0) {
			return i;
		}
	}
}

int index_last_negative (int arr[], int length)
{
	for (int i = length - 1; i >= 0; i--) {
		if (arr[i] < 0) {
			return i;
		}
	}
}

int sum_between_negative(int arr[], int length)
{
	int sum = 0;

	for (int i = index_first_negative(arr, length); i < index_last_negative(arr, length); i++) {
		sum += abs(arr[i]);
	}
	return sum;
}

int sum_before_and_after_negative(int arr[], int length)
{
	int sum = 0;

	for (int i = 0; i < length; i++) {
		if (i < index_first_negative(arr, length) || i >= index_last_negative(arr, length)) {
			sum += abs(arr[i]);
		}
	}
	return sum;
}

void case_choice(char command, int arr[], int length)
{
	switch(command) {
	case '0': 
	{
		printf("%d\n", index_first_negative(arr, length));
		break;
	}
	case '1':
	{
		printf("%d\n", index_last_negative(arr, length));
		break;
	}
	case '2':
	{
		printf("%d\n", sum_between_negative(arr, length));
		break;
	}
	case '3':
	{
		printf("%d\n", sum_before_and_after_negative(arr, length));
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
