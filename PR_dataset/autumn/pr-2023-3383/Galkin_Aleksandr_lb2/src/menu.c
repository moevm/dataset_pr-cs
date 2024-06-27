#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"


int main(void){
	int N = 101;
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
	switch(flag){
		case 0:
			printf("%d\n",index_first_negative(arr1, k));
			break;
		case 1:
			printf("%d\n",index_last_negative(arr1, k));
			break;
		case 2:
			printf("%d\n",sum_between_negative(arr1, k));
			break;
		case 3:
			printf("%d\n",sum_before_and_after_negative(arr1, k));
			break;
	}
	return 0;
}
