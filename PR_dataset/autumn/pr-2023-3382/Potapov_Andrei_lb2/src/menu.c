#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"


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
				printf("%d\n", sum_between_negative(Numbers, len_numbers));
				break;
			case 3:
				printf("%d\n", sum_before_and_after_negative(Numbers, len_numbers));
				break;
			default:
				printf("Данные некорректны\n");
		}
	} else{
		printf("Данные некорректны\n");
	}
	return 0;
}
