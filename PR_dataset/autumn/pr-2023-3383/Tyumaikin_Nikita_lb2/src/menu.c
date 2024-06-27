#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"


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
