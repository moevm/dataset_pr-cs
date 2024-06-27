#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#define maximum_size 20

void main(){
	int numbers[maximum_size];
	int action;
	char new_line;
	int size = 0;
	scanf("%d", &action);
	while(size < maximum_size){
		scanf("%d", &numbers[size]);
		size += 1;
		new_line = getchar();
		if(new_line == '\n'){
			break;
		}
	}	
	switch(action){
		case 0:
			printf("%d\n", index_first_negative(numbers, size));
			break;
		case 1:
			printf("%d\n", index_last_negative(numbers, size));
			break;
		case 2:
			printf("%d\n", multi_between_negative(numbers, size));
			break;
		case 3:
			printf("%d\n", multi_before_and_after_negative(numbers, size));
			break;
		default:
			printf("Данные некорректны\n");
	}
}