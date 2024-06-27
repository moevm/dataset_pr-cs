#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main(){
	int real_arr[100];
	int len_real_arr = 0;
	int n;
	scanf("%d", &n);
	char space = getchar();
	while(len_real_arr < 100 && space == ' '){
		scanf("%d", &real_arr[len_real_arr]);
		space = getchar();
		len_real_arr++;
	}
	switch (n) {
		case 0:
			printf("%d\n", abs_max(real_arr, len_real_arr));
			break;
		case 1:
			printf("%d\n", abs_min(real_arr, len_real_arr));
			break;
		case 2:
			printf("%d\n", diff(real_arr, len_real_arr));
			break;
		case 3:
			printf("%d\n", sum(real_arr, len_real_arr));
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}
