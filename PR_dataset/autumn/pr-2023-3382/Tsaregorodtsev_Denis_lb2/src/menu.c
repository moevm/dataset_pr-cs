#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
int main(){
	int a;
	scanf("%d",&a);
	int arr[100];
	int i;
	for(i=0;i<100;i++){
		arr[i]=0;
	}
	for(i=0;i<100;i++){
		scanf("%d",&arr[i]);
	}
	switch(a){
		case 0:
			printf("%d\n",index_first_even(arr));
			break;
		case 1:
			printf("%d\n",index_last_odd(arr));
			break;
		case 2:
			printf("%d\n",sum_between_even_odd(arr));
			break;
		case 3:
			printf("%d\n",sum_before_even_and_after_odd(arr));
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}

