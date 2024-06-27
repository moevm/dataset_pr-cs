#include <stdio.h>  
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

#define ARR_SIZE 100

int main()
{
	int realsize = 0;
	int command;
	int arr[ARR_SIZE];
	scanf("%d", &command);
	
	while (getchar() != '\n') {
		scanf("%d", &arr[realsize]);
		realsize++;
	}
	
	switch (command)
	{
	case 0:
		printf("%d", max(arr, realsize)); 
		break;
	case 1:
		printf("%d", min(arr, realsize)); 
		break;
	case 2:
		printf("%d", diff(arr, realsize)); 
		break;
	case 3:
		printf("%d", sum(arr, realsize)); 
		break;
	default:
		printf("Данные некорректны"); 
	}
}