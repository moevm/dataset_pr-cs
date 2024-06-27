#include<stdio.h>
#include<stdlib.h>
int index_first_even(int *arr,int size){
	int even;
	for(int i = 0; i< size; i++){
		if(arr[i]%2==0){
			even = i;
			break;
		}
	}
	return even;
}
int index_last_odd(int *arr, int size){
	int odd;
	for(int i = 0; i< size; i++){
		if(arr[i]%2!=0){
			odd=i;
		}
	}
	return odd;
}
int sum_between_even_odd(int *arr, int size){
	int fin = index_first_even(arr, size);
	int lin = index_last_odd(arr, size);
	int abs1 = 0;
	for(int i= fin; i < lin; i++){
		abs1 = abs1 + abs(arr[i]);
	}
	return abs1;
}
int sum_before_even_and_after_odd(int *arr, int size){
	int fin= index_first_even(arr, size);
	int lin = index_last_odd(arr, size);
	int abs2 = 0;
	for(int i=0; i < fin; i++){
		abs2 += abs(arr[i]);
	}
	for(int i= size-1; i >= lin; i--){
		abs2 += abs(arr[i]);
	}
	return abs2;
}
int main(){
	int a, b[100], d=0;
	scanf("%d",&a);
	for(int i=0;i<100;i++){
		char c;
		scanf("%d%c", &b[i], &c);
		d++;
		if (c=='\n'){
			break;
		}
	}
	switch(a){
		case 0:
		printf("%d", index_first_even(b,d));
		break;
		case 1:
		printf("%d", index_last_odd(b, d));
		break;
		case 2:
		printf("%d", sum_between_even_odd(b, d));
		break;
		case 3:
		printf("%d", sum_before_even_and_after_odd(b, d));
		break;
		default:
		printf("Данные некорректны");

	}
	return 0;
}