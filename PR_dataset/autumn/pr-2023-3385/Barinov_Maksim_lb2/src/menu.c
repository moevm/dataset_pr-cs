#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"


int main() {
	int k, n = 0;
	scanf("%d", &k);
	char c = ' ';
	int arr[100];
	while(c != '\n'){
		scanf("%d%c", &arr[n], &c);
		n++;
	}
	switch(k){
		case 0:
			printf("%d\n", max(n, arr));
			break;
		case 1:
			printf("%d\n", min(n, arr));
			break;
		case 2:
			printf("%d\n", diff(n, arr));
			break;
		case 3:
			printf("%d\n", sum(n, arr));
			break;
		default:
			printf("Данные некорректны\n");
			break;

	}
}
