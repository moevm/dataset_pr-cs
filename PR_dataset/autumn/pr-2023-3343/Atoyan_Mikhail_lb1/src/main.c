#include <stdio.h>  
#include <limits.h>

#define ARR_SIZE 100

int max(int a[], int size){
	int mx = INT_MIN;
	for (int i = 0; i < size; i++) {
		if (a[i] > mx) {
			mx = a[i];
		}
	}
	return mx;
}

int min(int a[], int size) {
	int mn = INT_MAX;
	for (int i = 0; i < size; i++) {
		if (a[i] < mn) {
			mn = a[i];
		}
	}
	return mn;
}

int diff(int a[], int size) {
	return max(a, size) - min(a, size);
}

int sum(int a[], int size) {
	int mn = min(a, size);
	int s = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] == mn) {
			break;
		}
		s += a[i];
	}
	return s;
}

int main()
{
	int realsize = 0;
	int command;
	int arr[ARR_SIZE];
	scanf("%d", &command);
	
	while (getchar() != '\n') {
		scanf("%d", &arr[realsize]);
		realsize++;
	}
	
	switch (command)
	{
	case 0:
		printf("%d", max(arr, realsize)); //Не забыл перенос строки
		break;
	case 1:
		printf("%d", min(arr, realsize)); //Не забыл перенос строки
		break;
	case 2:
		printf("%d", diff(arr, realsize)); //Не забыл перенос строки
		break;
	case 3:
		printf("%d", sum(arr, realsize)); //Не забыл перенос строки
		break;
	default:
		printf("Данные некорректны"); //Не забыл перенос строки
	}
}