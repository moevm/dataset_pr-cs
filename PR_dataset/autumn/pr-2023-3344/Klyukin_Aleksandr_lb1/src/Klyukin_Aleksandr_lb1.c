#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int lenght, int array[]){
	int i = 0;
	int left;
	for (i; i < lenght; i++){
		if (array[i] < 0){
			left = i;
			break;
		}
	}
	return left;
}
int index_last_negative(int lenght, int array[]){
	int i = 0;
	int right;
		for (i; i < lenght; i++){
			if (array[i] < 0){
				right = i;
			}
	}
	return right;
}
int sum_between_negative(int lenght,int array[]){
	int cnt;
	int left = index_first_negative(lenght, array);
	int right = index_last_negative(lenght, array);
		for (left; left < right; left++){
			cnt += abs(array[left]);
		}
		return cnt;
}
int sum_before_and_after_negative(int lenght, int array[]){
	int i = 0;
	int cnt;
	int left = index_first_negative(lenght, array);
	int right = index_last_negative(lenght, array);
	for (i; i<lenght; i++){
		if ((i < left) || (i >= right)){
			cnt += abs(array[i]);
		}
		else{
			continue;
		}
	}
	return cnt;
}
int main(){
	int arr[100] = {0};
	int i = 0;
	int m;
	char s;
	scanf("%d", &m);
    do{ 
        scanf("%d", &arr[i]); 
        i++; 
    } 
    while(getchar() != '\n');


	switch (m){
		case 0:{
			printf("%d\n", index_first_negative(100, arr));
			break;
		}
		case 1:{
			printf("%d\n", index_last_negative(100, arr));
			break;
		}
		case 2:{
			printf("%d\n", sum_between_negative(100, arr));
			break;
		}
		case 3:{
			printf("%d\n", sum_before_and_after_negative(100, arr));
			break;
		}
		default:{
			printf("Данные некорректны");
			break;
		}
	}
}
