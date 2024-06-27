#include <stdio.h>
#include "call_operation.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"
#include "index_first_negative.h"
#define NEW_LINE_INTEGER_FORMAT "%d\n"



void call_operation(int arr[], int count)
{
	switch(arr[0])
	{
		case 0:
			printf(NEW_LINE_INTEGER_FORMAT, index_first_negative(arr, count));
			break;
		case 1:
			printf(NEW_LINE_INTEGER_FORMAT, index_last_negative(arr, count));
			break;
		case 2:
			printf(NEW_LINE_INTEGER_FORMAT,
			sum_between_negative(arr, count));
			break;
		case 3:
			printf(NEW_LINE_INTEGER_FORMAT, sum_before_and_after_negative(arr, count));
			break;
		default:
			printf("Данные некоректны\n");
			
		
	}
	
}


