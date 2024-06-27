#include <stdio.h>
#include <stdlib.h>

int abs_max(int arr[], int len){
	int max_abs = abs(arr[0]);
	int res = arr[0];
	for (int i = 1; i < len; i++){
		if (abs(arr[i]) > max_abs){
		res = arr[i];
		max_abs = abs(arr[i]);
		}
	}
	return res;
}

int abs_min(int arr[], int len){
	int min_abs = abs(arr[0]);
	int res = arr[0];
	for (int i = 1; i < len; i++){
		if (abs(arr[i]) < min_abs){
			res = arr[i];
			min_abs = abs(arr[i]);
		}
	}
	return res;
}

int diff(int arr[], int len){
	int max = abs_max(arr, len);
	int min = abs_min(arr, len);
	return max - min;
}

int sum(int arr[], int len){
	int max = abs_max(arr, len);
	int begin_sum = 0;
	int sum_after_max = 0;
	for(int i = 0; i < len; i++){
		if(arr[i] == max && begin_sum == 0){
			begin_sum = 1;
		}
		if(begin_sum == 1){
			sum_after_max = sum_after_max + arr[i];
		}
	}
	return sum_after_max;
}

int main(){
	int max_size = 100;
	int len = 0;
	int arr[max_size];
	int option;
	char next_c;
	scanf("%d%c", &option, &next_c);
	while (len < max_size && next_c != '\n'){
		scanf("%d%c", &arr[len], &next_c);
		len++;
}
switch(option){
	case 0:
		printf("%d\n", abs_max(arr, len));
		break;
	case 1:
		printf("%d\n", abs_min(arr, len));
		break;
	case 2:
		printf("%d\n", diff(arr, len));
		break;
	case 3:
		printf("%d\n", sum(arr, len));
		break;
	default:
		puts("Данные некорректны\n");
		break;
	}	
	return 0;
}