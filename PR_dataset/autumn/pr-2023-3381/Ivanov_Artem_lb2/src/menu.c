#include <stdio.h>
#include <stdlib.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

#define N 1000
#define err "Данные некорректны"

int main() {
	int value, arr[N]; // операция/массив
	int len, flag = 0;
	char c = ' ';
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
