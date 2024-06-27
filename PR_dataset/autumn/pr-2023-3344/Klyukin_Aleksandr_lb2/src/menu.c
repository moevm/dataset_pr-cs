#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

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