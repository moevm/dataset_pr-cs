#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 100
#include "abs_min.h"
#include "abs_max.h"
#include "diff.h"
#include "sum.h"
int main(){
	int f, i=0,len_a;
	int a[N];
	char sp;
	scanf("%d%c", &f, &sp);
	do {
		scanf("%d%c", &a[i], &sp);
		i+=1;
	}while (sp !='\n');
	len_a=i;
	switch (f) {
		case 0:
			printf("%d\n", a[abs_max(a, len_a)]);
			break;
		case 1:
			printf("%d\n", a[abs_min(a, len_a)]);
			break;
		case 2:
			printf("%d\n", diff(a, len_a));
			break;
		case 3:
			printf("%d\n", sum(a, len_a));
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}