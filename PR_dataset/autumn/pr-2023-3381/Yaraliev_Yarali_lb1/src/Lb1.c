#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int res[],int len){
for(int i=0;i<len+1;i++){
	if(res[i]==0){
		return i;
	}else{
		if(i<len){
			continue;
		}else{
			return -1;
		}
	}
}
}

int index_last_zero(int res[],int len){
for(int i=len;i>=0;i--){
	if(res[i]==0){
		return i;
	}else{
		if(i>0){
			continue;
		}else{
			return -1;
		}
	}
}
}

int sum_between(int res[], int len) {
	int start = index_first_zero(res, len);
	int end = index_last_zero(res,len);
	if (start == -1 || end == -1) {
		return -1;
	}
	int sum = 0;
	for (int i = start + 1; i < end; i++) {
		sum += abs(res[i]);
	}
	return sum;
}

int sum_before_and_after(int res[], int len) {
	int start = index_first_zero(res, len);
	int end = index_last_zero(res, len);
	if (start == -1 || end == -1) {
		return-1;
	}
	int sum_before = 0;
	for (int i = 0; i < start; i++) {
		sum_before += abs(res[i]);
	}
	int sum_after = 0;
	for (int i = end + 1; i < len+1; i++) {
		sum_after += abs(res[i]);
	}
return sum_before + sum_after;
}


int main()
{
	int res[100]={};
	int a;
	int sum;
	int x;
	char end=' ';
	int len=0;
	scanf("%d\n", &x);
        len = 0;
        while (len < 100 && scanf("%d", &res[len]) != EOF && getchar() != '\n') {
            len++;
        }
	printf("\n");
	switch(x){
		case 0:
			if(index_first_zero(res, len)==-1){
				printf("Данные некорректны\n");
			}else{
				printf("%d\n", index_first_zero(res, len));
			}
			break;
		case 1:
			if(index_last_zero(res, len)==-1){
				printf("Данные некорректны\n");
			}else{
				printf("%d\n", index_last_zero(res, len));
			}
			break;
		case 2:
			printf("%d\n", sum_between(res, len));
			break;
		case 3:
			printf("%d\n", sum_before_and_after(res, len));
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}

