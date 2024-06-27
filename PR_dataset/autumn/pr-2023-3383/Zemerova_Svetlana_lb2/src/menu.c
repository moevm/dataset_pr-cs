#define N 100
#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main()
{
	int number;
	scanf ("%d",&number);
	int mas[N];
	int i=0;
	int c;
	while ((c=getchar())!='\n')
	{
		scanf("%d",&mas[i]);
		++i;
	}
	int ln=i;
	switch (number)
	{
		case 0:
			printf("%d\n", mas[abs_max(mas,ln)]);
			break;
		case 1:
			printf("%d\n", abs_min(mas,ln));
			break;
		case 2:
			printf("%d\n", diff(mas,ln));
			break;
		case 3:
			printf("%d\n", sum(mas,ln));
			break;
		default:
			puts("Данные некорректны\n");
	}
	return 0;
}
