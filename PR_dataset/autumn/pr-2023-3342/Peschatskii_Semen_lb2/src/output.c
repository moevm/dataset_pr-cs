#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#include "output.h"
#define FORM "%d\n"
void output(int option, int list[], int list_len){
	switch(option){
	case 0:
		printf(FORM, index_first_negative(list, list_len));
		break;
	case 1:
		printf(FORM, index_last_negative(list, list_len));
		break;
	case 2:
		printf(FORM, sum_between_negative(list, list_len));
		break;
	case 3:
		printf(FORM, sum_before_and_after_negative(list, list_len));
		break;
	default:
		printf("Данные некорректны\n");
	}
}
