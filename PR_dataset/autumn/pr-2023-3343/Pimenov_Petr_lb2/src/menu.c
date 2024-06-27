#include <stdio.h>

#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

#define MAX_SIZE 100

int main(){
	int mode;
	int size=0;
	int arr[MAX_SIZE];

	scanf("%d", &mode);
	while(getchar() != '\n'){
		scanf("%d", &arr[size]);
		size++;
	}
	
	switch(mode){
		case 0:
			printf("%d\n", index_first_zero(arr, size));
			break;
		case 1:
			printf("%d\n", index_last_zero(arr, size));
			break;
		case 2:
			printf("%d\n", sum_between(arr, size));
			break;
		case 3:
			printf("%d\n", sum_before_and_after(arr, size));
			break;
		default:
			printf("%s\n","Данные некорректны");
			break;
	}

	return 0;
}
