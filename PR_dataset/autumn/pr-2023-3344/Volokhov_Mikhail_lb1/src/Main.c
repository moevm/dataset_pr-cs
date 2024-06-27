#include <stdio.h>

int FindMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int FindMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int FindDiff(int arr[], int size) {
    int max = FindMax(arr, size);
    int min = FindMin(arr, size);
    if (min < 0){
        return max + min;
    }else{
        return max - min;
    }
}

int FindSumBeforeMin(int arr[], int size) {
    int min = FindMin(arr, size);
    int sum = 0;
    for (int i = 0; i <= size; i++)
	{
		if (arr[i] != min){
			sum += arr[i];
		} else {
			break;
		}
	}
	return sum;
}

void Do_choice(int arr[], int size, int choice)
{
	int result;

	switch (choice) {
        case 0:
            printf("%d\n",FindMax(arr, size));
            break;
        case 1:
            printf("%d\n",FindMin(arr, size));
            break;
        case 2:
            printf("%d\n",FindDiff(arr, size));
            break;
        case 3:
            printf("%d\n",FindSumBeforeMin(arr, size));
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

	Do_choice(array, size, choice);
	return 0;
}