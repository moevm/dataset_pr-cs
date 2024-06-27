#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

int index_first_even(int arr[], int size) {
	for (int i = 0; i < size; i++)
	{
		if (abs(arr[i]) % 2 == 0) 
			return i;
	}
}

int index_last_odd(int arr[], int size) {
	int ind = 0;
	for (int i =0; i<size; i++) 
	{
		if (abs(arr[i]) % 2 != 0) 
			ind=i;
	}
	return ind;
}
int sum_between_even_odd(int a, int b, int arr[], int size)
{
	int sum_between_even_odd = 0;
	for (int i = 0; i < size; i++)
	{
		if ((i >= a) && (i < b))
			sum_between_even_odd += abs(arr[i]);
	}
	return sum_between_even_odd;
}

int sum_before_even_and_after_odd (int a, int b, int arr[], int size)
{
	int sum_before_even_and_after_odd = 0;
	for (int i = 0; i < size; i++)
	{
		if ((i < a) || (i >= b))
			sum_before_even_and_after_odd += abs(arr[i]);
	}
	return sum_before_even_and_after_odd;
}

int main()
{
	//function number input
	int choice;
	scanf("%d", &choice);

	//array input
	int array[MAX_SIZE];
	int size_updated = 0;
	while (getchar() != '\n')
	{
		scanf("%d", &array[size_updated]);
		size_updated++;
	}
	
	//switching functions
	switch (choice)
	{
	case 0:
		printf("%d", index_first_even(array, size_updated));
		break;

	case 1:
		printf("%d", index_last_odd(array, size_updated));
		break;

	case 2:
		printf("%d", sum_between_even_odd(index_first_even(array, size_updated),
			index_last_odd(array, size_updated), array, size_updated));
		break;

	case 3:
		printf("%d", sum_before_even_and_after_odd(index_first_even(array, size_updated),
			index_last_odd(array, size_updated), array, size_updated));
		break;

	default:
		printf("Данные некорректны");
		break;
	}
}
