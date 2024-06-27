#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#define N 100
int input(int *option, int num_list[]){int i=0; char end_checker;
	scanf("%d", option);
	while(end_checker!='\n' && i<N){
		scanf("%d%c", &num_list[i++], &end_checker);
	}
	return i;
}
