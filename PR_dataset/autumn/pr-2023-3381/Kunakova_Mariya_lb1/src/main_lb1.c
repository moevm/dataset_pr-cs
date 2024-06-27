#include <stdio.h>
#include <stdlib.h>
int abs_max(int arr[], int len_arr) {
	int max = 0;
	for(int i = 0; i < len_arr; i++){
	    if (abs(arr[i]) > abs(max)){
	        max = arr[i];
	    }
	}
	return max;
}
int abs_min(int arr[], int len_arr) {
	int min = abs(abs_max(arr, len_arr));
	for(int i = 0; i < len_arr; i++){
	    if (abs(arr[i]) < abs(min)){
	        min = arr[i];
	    }
	}
	return min;
}
int diff(int arr[], int len_arr) {
	int difference = abs_max(arr, len_arr) - abs_min(arr, len_arr);
	return difference;
}
int sum(int arr[], int len_arr) {
	int flag = 0;
	int max = abs_max(arr, len_arr);
	int summa = 0;
	for (int i = 0; i < len_arr; i++) {
		if (arr[i] == max) {
			flag = 1;
		}
		if (flag == 1) {
			summa += arr[i];
		}
	}
	return summa;
}
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