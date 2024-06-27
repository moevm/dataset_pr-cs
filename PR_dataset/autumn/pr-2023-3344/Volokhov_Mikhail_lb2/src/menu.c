#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

void menu(int arr[], int size, int choice)
{
	int result;
	switch (choice) {
        case 0:
            printf("%d\n",max(arr, size));
            break;
        case 1:
            printf("%d\n",min(arr, size));
            break;
        case 2:
            printf("%d\n",diff(arr, size));
            break;
        case 3:
            printf("%d\n",sum(arr, size));
            break;
        default:
            printf("Данные некорректны\n");
    }
	return;
}

int main(void)
{
	int choice;
	int array[100];
	int element;
	char end_char;
	int size = 0;

	scanf("%d", &choice);
	do {
		end_char = getchar();
		if (end_char == '\n') {
            break;
        }
		scanf("%d", &element);
		array[size++] = element;
	}while (1);

	menu(array, size, choice);
	return 0;
}