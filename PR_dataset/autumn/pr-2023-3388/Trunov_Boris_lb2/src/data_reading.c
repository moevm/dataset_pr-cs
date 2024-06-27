#include <stdio.h>
#include "data_reading.h"
#define MAX_SIZE_ARR 20
void data_reading(int arr[], int * operation, int * arr_count_items){
	scanf("%d", operation);
	do{
		if (*arr_count_items < MAX_SIZE_ARR){
			scanf("%d", &arr[(*arr_count_items)++]);
		}
	}while(getchar() != '\n');
}
