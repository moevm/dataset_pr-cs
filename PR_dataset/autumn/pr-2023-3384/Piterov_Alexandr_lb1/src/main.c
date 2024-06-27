#include <stdio.h>
#include <stdlib.h> // abs()

#define ARRAY_MAX_CAP 100

int index_first_even(int* arr, int len){
	
	int index = -1;
	for(int i = 0; i < len; i++){
		
		if(arr[i] % 2 == 0){
			index = i;
			break;
		}
	}

	return index;
}


int index_last_odd(int* arr, int len){
	
	int index = -1;
	for(int i = len - 1; i >= 0; i--){
		
		if(arr[i] % 2 != 0){
			index = i;
			break;
		}
	}

	return index;;
}


int sum_between_even_odd(int* arr, int len){

	int even = index_first_even(arr, len);
	int odd = index_last_odd(arr, len);

	// [DEBUG]
	// printf("Even index: %d\nOdd  index: %d\n", even, odd);

	int sum = 0;
	for(int i = even; i < odd; i++){
		sum += abs(arr[i]);
	}

	return sum;
}


int sum_before_even_and_after_odd(int* arr, int len){

	int even = index_first_even(arr, len);
	int odd = index_last_odd(arr, len);

	int sum = 0;
	for(int i = 0; i < even; i++){
		sum += abs(arr[i]);
	}
	for(int i = odd; i < len; i++){
		sum += abs(arr[i]);
	}

	// Можно заменить на один цикл, проходящий по всем элементам, но с дополнительным условием if(i < even && i >= odd){ sum += ... }, но так больше операций.

	return sum;
}


int main(){

	int task_id;
	int arr_len;
	int arr[ARRAY_MAX_CAP];


	// Парсинг значений
	int res;
	scanf("%d", &task_id);
	for(int i = 0; i < ARRAY_MAX_CAP; i++){
		res = scanf(" %d", &arr[i]);
		if(res == EOF){
			arr_len = i; // В связи с тем, что индексация массивов начинается с нуля, чтобы из последнего индекса получить длину массива, нужно добавить 1. Но уже взят лишний символ из буфера, который оказался EOF, поэтому i на единицу больше, что и требовалось. 
			break;
		}
	}

	// [DEBUG]
	/*
	printf("Task id: %d\n", task_id);
	printf("Array len: %d\n", arr_len);
	for(int i = 0; i < ARRAY_MAX_CAP; i++)
		printf("%d ", arr[i]);
	*/
	

	// Меню. Выбор подзадачи
	switch(task_id){
		case 0:
			printf("%d\n", index_first_even(arr, arr_len));
			break;
		case 1:
			printf("%d\n", index_last_odd(arr, arr_len));
			break;
		case 2:
			printf("%d\n", sum_between_even_odd(arr, arr_len));
			break;
		case 3:
			printf("%d\n", sum_before_even_and_after_odd(arr, arr_len));
			break;
		default:
			puts("Данные некорректны\n");
			break;
	}

	return 0;
}
