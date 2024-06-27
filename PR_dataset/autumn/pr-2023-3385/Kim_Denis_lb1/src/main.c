#include <stdio.h>
#include <math.h>
#define Max_size 100
#include <stdlib.h>
int index_first_even(int *array, int size_array){
	int even;
	for(int i=0; i<size_array; i++){
		if(array[i]%2==0){
			even = i;
			break;
	}
	}
	return even;
}
int index_last_odd(int *array, int size_array){
	int odd;
	for(int i=0; i<size_array; i++){
		if(array[i]%2!=0){
			odd = i;
		}
	}
	return odd;
}
int sum_between_even_odd(int *array, int size_array){
	int first_index = index_first_even(array, size_array);
	int last_index = index_last_odd(array, size_array);
	int abs_sum_between = 0;
	for(int i = first_index; i < last_index; i++){
		abs_sum_between = abs_sum_between + abs(array[i]);
	}
	return abs_sum_between;
}
int sum_before_even_and_after_odd(int *array, int size_array){
	int first_index = index_first_even(array, size_array);
	int last_index = index_last_odd(array,size_array);
	int abs_sum = 0;
	for(int i =0; i < first_index; i++){
		abs_sum += abs(array[i]);
	}
	for(int i = last_index; i < size_array; i++){
		abs_sum += abs(array[i]);
	}
	return abs_sum;
}
int main(){
	int operation, result;
	result = 0;
	scanf("%d", &operation);
	int size = 0;
	int arr[Max_size];
	char end_line;
	do{
		scanf("%d%c", &arr[size], &end_line);
		size++;
	}while(end_line!='\n');
	switch(operation){
		case 0:
			result = index_first_even(arr, size);
			printf("%d\n", result);
			break;
		case 1:
			result =index_last_odd(arr, size);
			printf("%d\n", result);
			break;
		case 2:
			result =sum_between_even_odd(arr, size);
			printf("%d\n", result);
			break;
		case 3:
			result =sum_before_even_and_after_odd(arr, size);
			printf("%d\n", result);
			break;
		default:
			puts("Данные некорректны");
			break;
	}
	return 0;
}
