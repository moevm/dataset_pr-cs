#include "input.h"
int input(int *arr){
	int res = 0;
	while(getchar() != '\n') {
		scanf("%d", &arr[res++]);
	}
	return res;
}
