#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

#define PAIR arr, arr_len
#define INT "%d\n"

void function_select(int arr[], int arr_len, int task) {
	switch(task) {
	case 0: {
	    printf(INT, index_first_zero(PAIR));
	    break;
    }
	case 1: {
	    printf(INT, index_last_zero(PAIR));
	    break;
	}
	case 2: {
	    printf(INT, sum_between(PAIR));
	    break;
	}
	case 3: {
	    printf(INT, sum_before_and_after(PAIR));
	    break;
	}
	default: {
	    printf("Данные некорректны");
	    break;
    }
    }
}