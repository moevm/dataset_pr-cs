#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

#define BUFFER 100


int main(void)
{
	int choice;
	int array[BUFFER];
	int element;
	char last_ch;
	int arr_len = 0;

	scanf("%d", &choice);

	do {
		last_ch = getchar();
		if (last_ch == '\n') {
            break;
        }
		scanf("%d", &element);
		array[arr_len++] = element;
	}while (1);

	arr_len--;
	int result;

	switch(choice){
    case 0:
        result =  get_max(array, arr_len);
		break;
    case 1:
        result = get_min(array, arr_len);
		break;
    case 2:
        result = get_diff(array, arr_len);
		break;
    case 3:
        result = get_sum_bf_min(array, arr_len);
		break;
	default:
		printf("Данные некорректны\n");
		return 0;
    }

	printf("%d\n", result);
	return 0;
}