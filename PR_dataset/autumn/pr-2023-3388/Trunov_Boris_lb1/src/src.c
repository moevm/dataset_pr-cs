#include <stdio.h>
int index_first_negative(int arr[], int count){
	int index = 0;
	for (int x = 1; x < count; x++){
		if(arr[x] < 0){
			return index;
			break;
		}
		index++;
	}
	return -1;
}
int index_last_negative(int arr[], int count){
	int index = count - 2;
	for (int x = count - 1; x >= 1; x--){
		if(arr[x] < 0){
			return index;
			break;
		}
		index--;
	}
	return -1;
}
int multi_between_negative(int arr[], int count){
	int first_negative = index_first_negative(arr, count);
	int last_negative = index_last_negative(arr, count);
	int multi_result = 1;
	for (int x = first_negative + 1; x < last_negative + 1; x ++){
		multi_result *= arr[x];
	}
	return multi_result;
}
int multi_before_and_after_negative(int arr[], int count){
	int first_negative = index_first_negative(arr, count);
	int last_negative = index_last_negative(arr, count);
	int multi_result = 1;
	for (int x = 1; x < first_negative + 1; x++){
		multi_result *= arr[x];
	}
	for (int x = last_negative + 1; x < count; x++){
		multi_result *= arr[x];
	}
	return multi_result;
}
int main(){
	int count = 0;
	int arr[21];
	do{
		if (count < 21){
			scanf("%d", &arr[count++]);
		}
	}while(getchar() != '\n');
	int operation = arr[0];
	switch(operation){
		case 0:
			printf("%d\n", index_first_negative(arr, count));
			break;
		case 1:
			printf("%d\n", index_last_negative(arr, count));
			break;
		case 2:
			printf("%d\n", multi_between_negative(arr, count));
			break;
		case 3:
			printf("%d\n", multi_before_and_after_negative(arr, count));
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}
