#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int arr[], int size);
int index_last_zero(int arr[], int size);
int sum_between(int arr[], int size);
int sum_before_and_after(int arr[], int size);

int main(){
	int mode;
	int size=0;
	int arr[100];

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

int index_first_zero(int arr[], int size){
	int first_index = -1;
	for (int i = 0; i < size; i++){
		if (arr[i] == 0) {
			first_index = i;
			break;			
		}
	}
	return first_index;
}

int index_last_zero(int arr[], int size){
	int last_index = -1;
	for (int i = size - 1; i >= 0; i--){
		if (arr[i] == 0){
			last_index = i;
			break;
		}
	}
	return last_index;
}

int sum_between(int arr[], int size){
	int first_index = index_first_zero(arr, size);
	int last_index = index_last_zero(arr, size);
	int sum = 0;
	for (int i = first_index; i <= last_index; i++){
		sum += abs(arr[i]);
	}
	return sum;
}

int sum_before_and_after(int arr[], int size){
	int first_index = index_first_zero(arr, size);
	int last_index = index_last_zero(arr, size);
	int sum = 0;
	for (int i = 0; i <= first_index; i++){
		sum += abs(arr[i]);
	}
	for (int j = last_index; j < size; j++){
		sum += abs(arr[j]);
	}
	return sum;
}