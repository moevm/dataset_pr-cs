#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#define maxN 100

int main(){
	int task_key;
	int arr[maxN], arrsum[maxN];
	int num = 0, abs_sum = 0, zero = 0, CNT_ARR = 0;
	char enter;

	scanf("%d", &task_key);

	while (num < maxN && enter != '\n'){
		scanf("%d%c", &arr[num], &enter);
		abs_sum = abs_sum + abs(arr[num]);
		arrsum[num] = abs_sum;
		if (arr[num] == 0) zero += 1;
		num++;
	}

	if (zero == 0){ puts("Данные некорректны"); return 0; }

	CNT_ARR = num;

	switch(task_key){
		case 0:
			printf("%d\n", index_first_zero(arr, CNT_ARR));
			break;
		case 1:
			printf("%d\n", index_last_zero(arr, CNT_ARR));
			break;
		case 2:
			printf("%d\n", sum_between(arr, arrsum, CNT_ARR));
			break;
		case 3:
			printf("%d\n", sum_before_and_after(arr, arrsum, CNT_ARR));
			break;
		default:
			puts("Данные некорректны");
	}
	return 0;
}