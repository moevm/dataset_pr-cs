#include <stdio.h>
#include <stdlib.h>

#define N 101

int index_first_negative(int arr[]){
	for(int i=0; i<N; i++){
		if(arr[i]<0){
			return i;
		}
	}
}

int index_last_negative(int arr[], int n){
	for(int i = (n-1); i> 0; i--){
		if(arr[i]<0){
			return i;
		}
	}
}

int sum_between_negative(int arr[], int a, int b){
	int sum = 0;
	for(int i = a; i<b; i++){
		sum  = sum + abs(arr[i]);	
	}
	return sum;
}

int sum_before_and_after_negative(int arr[], int a, int b, int n){
	int sum = 0;
	for(int i = 0; i<a; i++){
		sum = sum + abs(arr[i]);
	}
	for(int i = b; i<n; i++){
		sum = sum + abs(arr[i]);
	}
	return sum;
}

void main(){
	int flag;
	int arr[N];
	int k=-1;
	for(int i = 0; i<N; i++){
		scanf("%d", &arr[i]);
		k++;
		char c = getchar();
		if (c == '\n') break;
	}
	flag=arr[0];
	if(flag<0 || flag>3){
		printf("%s","Данные некорректны\n");
        }
	int arr1[k];
	int j=0;
	for(int i = 1; i<=k; i++){
		arr1[j]=arr[i];
		j++;
	}
	int first_neg = index_first_negative(arr1);
	int last_neg = index_last_negative(arr1,k);
	switch(flag){
		case 0:
			printf("%d\n",index_first_negative(arr1));
			break;
		case 1:
			printf("%d\n",index_last_negative(arr1,k));
			break;
		case 2:
			printf("%d\n",sum_between_negative(arr1,first_neg,last_neg));
			break;
		case 3:
			printf("%d\n",sum_before_and_after_negative(arr1,first_neg,last_neg,k));
			break;
	}
}
