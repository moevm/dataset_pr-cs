#include <stdio.h>

#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

#define ARRAY_MAX_CAP 100


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
			arr_len = i; 
			break;
		}
	}


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
