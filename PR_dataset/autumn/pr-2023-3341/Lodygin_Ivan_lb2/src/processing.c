#include <stdio.h>
#include "function_select.h"

#define STR_SIZE 101

void processing() {
	int task;
	char space;
	scanf("%d%c", &task, &space);
	space = 0;
	int arr[STR_SIZE];
	int arr_len = 0;
	while (space != '\n') {
		scanf("%d%c", &arr[arr_len], &space);
		arr_len++;
	}
	function_select(arr, arr_len, task);
}