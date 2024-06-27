#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int arr[], int l){
	for(int i=0; i<l;i++){
		if(arr[i]<0){
			return i;
			break;	
		}	
	}	
}

int index_last_negative(int arr[], int l){
	for(int i=l;i>=0;i--){
		if(arr[i]<0){
			return i;
			break;
		}	
	}	
}	
int sum_between_negative(int index_f, int index_l,int arr[]){
	int sum=0;
	for(int i=index_f;i<index_l;i++){
		sum =  sum + abs(arr[i]);
	}	
	return sum;
}	
int sum_before_and_after_negative(int index_f, int index_l, int arr[], int l){
	int sum=0;
	for(int i=0; i<index_f;i++){
		sum = sum + abs(arr[i]);
	}	
	for(int i=index_l;i<=l;i++){
		sum =  sum + abs(arr[i]);
	}	
	return sum;
}	

int main(){
	int Numbers[200];
	int command,len_numbers=-1;
	scanf("%d", &command);
	char razd;
	int negatives=0;
	while (razd != '\n'){
		len_numbers++;
		scanf("%d%c", &Numbers[len_numbers], &razd);
		if (Numbers[len_numbers]<0){
			negatives=1;
		}	
	}	
	if (negatives){
		switch(command){
			case 0:
				printf("%d\n", index_first_negative(Numbers, len_numbers));
				break;
			case 1:
				printf("%d\n", index_last_negative(Numbers, len_numbers));
				break;
			case 2:
				printf("%d\n", sum_between_negative(index_first_negative(Numbers, len_numbers), index_last_negative(Numbers, len_numbers), Numbers));
				break;
			case 3:
				printf("%d\n", sum_before_and_after_negative(index_first_negative(Numbers, len_numbers), index_last_negative(Numbers, len_numbers), Numbers, len_numbers));
				break;
			default:
				printf("Данные некорректны\n");
		}
	} else{
		printf("Данные некорректны\n");
	}	
}

