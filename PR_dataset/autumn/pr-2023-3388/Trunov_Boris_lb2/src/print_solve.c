#include <stdio.h>
#include "print_solve.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#define PRINT_DOUBLE "%d\n"

void print_solve(int arr[], int operation, int arr_count_items){
	switch(operation){
		case 0:
			printf(PRINT_DOUBLE, index_first_negative(arr, arr_count_items));
			break;
		case 1:
			printf(PRINT_DOUBLE, index_last_negative(arr, arr_count_items));
			break;
		case 2:
			printf(PRINT_DOUBLE, multi_between_negative(arr, arr_count_items));
			break;
		case 3:
			printf(PRINT_DOUBLE, multi_before_and_after_negative(arr, arr_count_items));
			break;
		default:
			printf("Данные некорректны\n");
			break;
	}
}
