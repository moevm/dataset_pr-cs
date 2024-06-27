#include <stdio.h>
#include <stdlib.h>

#define N 2000
#define err "Данные некорректны"

//функция для значения 0
int index_first_negative(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		if (arr[i] < 0) {
			return i;
			break;
		}
	}
}

//функция для значения 1
int index_last_negative(int arr[], int len) {
	for (int i = len; i >= 0; i--) {


		if (arr[i]<0) {
			return i;
		}
	}
}

//функция для значения 2
int sum_between_negative(int arr[], int len) {
	int sum = 0;
	for (int i = index_first_negative(arr, len); i < index_last_negative(arr, len); i++) {
		sum = sum + abs(arr[i]);
	}
	return sum;
}

//функция для значения 3
int sum_before_and_after_negative(int arr[], int len) {
	/*int sum = 0;
	for (int i = 0; i < len; i++) {
		sum = sum + abs(arr[i]);
	}
	return sum-sum_between_negative(arr, len);*/
	int sum = 0;
	for (int i = 0; i < index_first_negative(arr, len); i++) {
		sum = sum + abs(arr[i]);
	}
	for (int i = index_last_negative(arr, len); i < len; i++) {
		sum = sum + abs(arr[i]);
	}
	return sum;
}

int main() {
	int value, arr[N]; // операция/массив
	int len, flag = 0;
	scanf("%d", &value); // считывание номера операции

// заполнение массива чисел числами
	while (getchar()!='\n') {
		scanf("%d", &arr[len]);
		if (arr[len]<0) {
			flag = 1;
		}
		len++;
	}
	if (flag == 1) {
		switch(value) {
			case 0:
				printf("%d\n", index_first_negative(arr, len));
				break;
			case 1:
				printf("%d\n", index_last_negative(arr, len));
				break;
			case 2:
				printf("%d\n", sum_between_negative(arr, len));
				break;
			case 3:
				printf("%d\n", sum_before_and_after_negative(arr, len));
				break;
			default:
				printf(err);
			break;
		}
	}
	else {
		printf(err);
	}
}


