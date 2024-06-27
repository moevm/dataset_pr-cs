//problem 3
#include <stdlib.h>
#include <stdio.h>


//two separate functions here can be easily merged to one this way: for(int i = (mode == 0)?0:arr_len; (mode == 0 && i < arr_len)||(mode == 1 && i >= 0); i += 1 - (2*mode))
//leaving them splitted 'cause of the task

int index_first_zero(int arr[], int arr_len)
{
	for(int i = 0; i < arr_len; i++)
	{
		if(arr[i] == 0) {return i;}
	}
	return 0;  //program will never reach this point, nevertheless I've added this line to prevent compiler warning 
}

int index_last_zero(int arr[], int arr_len)
{
	for(int i = arr_len-1; i >= 0; i--)
	{
		if(arr[i] == 0) {return i;}
	}
	return 0;  //program will never reach this point, nevertheless I've added this line to prevent compiler warning 
}

int sum_between(int arr[], int arr_len)
{
	int result = 0;
	for(int i = index_first_zero(arr, arr_len)+1; i < index_last_zero(arr, arr_len); i++) {result += abs(arr[i]);}
	return result;
}

int sum_before_and_after(int arr[], int arr_len)
{
	int result = 0;
	for(int i = 0; i < index_first_zero(arr, arr_len); i++) {result += abs(arr[i]);}
	for(int i = index_last_zero(arr, arr_len); i < arr_len; i++) {result += abs(arr[i]);}
	return result;
}

int main()
{
	//reading mode and array from stdin
	int mode = 0;
	int arr_len = 0;
	int arr[100];
	char delimiter;
	scanf("%d", &mode);
	delimiter = getchar();
	for(arr_len = 0; arr_len < 100 && delimiter == ' '; arr_len++)
	{
		scanf("%d", &arr[arr_len]);
		delimiter = getchar();
	}

	//find selected value
	switch(mode)
	{
		case 0:
			printf("%d\n", index_first_zero(arr, arr_len));
			break;

		case 1:
			printf("%d\n", index_last_zero(arr, arr_len));
			break;

		case 2:
			printf("%d\n", sum_between(arr, arr_len));
			break;

		case 3:
			printf("%d\n", sum_before_and_after(arr, arr_len));
			break;

		default:
			printf("Данные некорректны\n");
			break;
	}
	return 0;
}