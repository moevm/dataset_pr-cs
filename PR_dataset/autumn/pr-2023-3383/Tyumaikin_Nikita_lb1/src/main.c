#include <stdio.h>
#include <stdlib.h>


int index_first_even(int *arr, int len){
	for(int i=0;i<len;++i){
		if (arr[i] % 2 == 0)
			return i;
	}
}

int index_last_odd(int *arr, int len){
	for(int i=len - 1;i >= 0;--i){
		if (arr[i] % 2 != 0)
			return i;
	}
}

int sum_between_even_odd(int *arr, int len){
	int sum = 0;
	for(int i=index_first_even(arr, len);i<index_last_odd(arr, len);++i){
		sum += abs(arr[i]);
	}
	return sum;
}


int sum_before_even_and_after_odd(int *arr, int len){
	int sum = 0;
	for(int i=0; i<index_first_even(arr, len);++i){
		sum += abs(arr[i]);
	}

	for(int i=index_last_odd(arr,len); i<len;++i){
		sum += abs(arr[i]);
	}
	return sum;
}




int main(){
	int mode;
	int* arr = NULL;
	char a;
	scanf("%d", &mode);
	if(mode<0 || mode>3){
		printf("%s","Данные некорректны\n");
    }
	getchar();
	arr = malloc(sizeof(int));
	int i;
	for(i=1;i<101;++i){
		arr = realloc(arr, sizeof(int)*i);
		scanf("%d", (arr+i-1));
		a = getchar();
		if (a=='\n') 
			break;
	}
	int len = i;
	switch(mode){
		case 0:
			printf("%d\n",index_first_even(arr, len));
			break;
		case 1:
			printf("%d\n",index_last_odd(arr,len));
			break;
		case 2:
			printf("%d\n",sum_between_even_odd(arr, len));
			break;
		case 3:
			printf("%d\n",sum_before_even_and_after_odd(arr,len));
			break;
	}
	return 0;
}
