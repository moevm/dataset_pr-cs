#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#include "get_one_int.h"
#include "fill_array_and_get_len.h"

int main(){
	int one_int = get_one_int();
	int array[100];
	int len = fill_array_and_get_len(array);

	switch(one_int){	
		case 0:
			printf("%d\n",index_first_zero(array, len));
			break;
		case 1:
			printf("%d\n",index_last_zero(array, len));
			break;
		case 2: 
			printf("%d\n",sum_between(array,len));
			break;
		case 3:
			printf("%d\n",sum_before_and_after(array,len));
			break;
		default:
			puts("Данные некорректны");
	}


	return 0;
}
