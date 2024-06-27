#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int index_negative(int *arr, int size, int dir);
int summ_arr(int *arr, int left, int right);

void index_first_negative(int *arr, int size){
	printf("%d\n", index_negative(arr, size, 1));
}
void index_last_negative(int *arr, int size){
	printf("%d\n", index_negative(arr, size, -1));
}
void sum_between_negative(int *arr, int size){
	int left, right;
	left = index_negative(arr, size, 1);
	right = index_negative(arr, size, -1);
	printf("%d\n", summ_arr(arr, left, right));
}
void sum_before_and_after_negative(int *arr, int size){
	int to_left, from_right;
	to_left = index_negative(arr, size, 1);
	from_right = index_negative(arr, size, -1);
	printf("%d\n", summ_arr(arr, 0, to_left) + summ_arr(arr, from_right, size));
}

int main(){
	int arr[MAXSIZE];
	int task, size = 0;
	scanf("%d", &task);
	while(getchar() != '\n') {
		scanf("%d", &arr[size++]);
	}
	switch(task){
		case 0:
			index_first_negative(arr, size);
			break;
		case 1:
			index_last_negative(arr, size);
			break;
		case 2:
			sum_between_negative(arr, size);
			break;
		case 3:
			sum_before_and_after_negative(arr, size);
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}

int index_negative(int *arr, int size, int dir){
	int i = 0;
	if (dir < 0)
		i = size - 1;
	for (; (i < size) && (i > -1); i = i + dir){
		if (arr[i] < 0)
			return i;
	}
	return -1;
}
int summ_arr(int *arr, int left, int right){
	int res = 0;
	for(int i = left; i < right; ++i)
		res = res + abs(arr[i]);
	return res;
}
