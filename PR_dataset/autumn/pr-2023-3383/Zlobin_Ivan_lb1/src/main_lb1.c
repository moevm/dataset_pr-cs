#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int arr[]){
	for(int i=0;i<100;++i){
		if(arr[i]<0)
			return i;
	}
}

int index_last_negative(int arr[]){
	for(int i=99;i>=0;--i){
		if(arr[i]<0)
			return i;
	}
}

int sum_between_negative(int arr[]){
	int sum=0;
	for(int i=index_first_negative(arr);i<index_last_negative(arr);++i){
		sum+=abs(arr[i]);
	}
	return sum;
}

int sum_before_and_after_negative(int arr[]){
       int sum=0,i;
       for(i=0;i<index_first_negative(arr);++i){
	       sum+=abs(arr[i]);
       }
       for(i=index_last_negative(arr);i<100;++i){
	       sum+=abs(arr[i]);
       }
       return sum;
}       

int main(){
	int arr[100]={0};
	int n; scanf("%d", &n);
	for(int i=0;i<100;++i){
		scanf("%d",&arr[i]);
		if(getchar()=='\n')
			break;
	}
	switch(n){
		case 0:
			printf("%d\n",index_first_negative(arr));
			break;

		case 1:
			printf("%d\n",index_last_negative(arr));
			break;
		
		case 2:
			printf("%d\n",sum_between_negative(arr));
			break;

		case 3:
			printf("%d\n",sum_before_and_after_negative(arr));
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}

