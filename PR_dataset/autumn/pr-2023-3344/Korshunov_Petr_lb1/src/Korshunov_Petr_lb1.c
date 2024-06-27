#include <stdio.h>

#define BUFFER 100


int get_max(int arr[], int arr_len);
int get_min(int arr[], int arr_len);
int get_diff(int arr[], int arr_len);
int get_sum_bf_min(int arr[], int arr_len);
void make_choice(int arr[], int arr_len, int choice);


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
	make_choice(array, arr_len, choice);

	return 0;
}


void make_choice(int arr[], int arr_len, int choice)
{
	int result;

	switch(choice){
    case 0:
        result =  get_max(arr, arr_len);
		break;
    case 1:
        result = get_min(arr, arr_len);
		break;
    case 2:
        result = get_diff(arr, arr_len);
		break;
    case 3:
        result = get_sum_bf_min(arr, arr_len);
		break;
	default:
		printf("Данные некорректны\n");
		return;
    }

	printf("%d\n", result);
	return;
}


int get_max(int arr[], int arr_len)
{
	int max = arr[0];

	for (int i = 0; i <= arr_len; i++)
	{
		if (arr[i] > max){
			max = arr[i];
		}
	}
	return max;
}


int get_min(int arr[], int arr_len)
{
	int min = arr[0];

	for (int i = 0; i <= arr_len; i++)
	{
		if (arr[i] < min){
			min = arr[i];
		}
	}
	return min;
}


int get_diff(int arr[], int arr_len)
{
	int diff = get_max(arr, arr_len) - get_min(arr, arr_len);
	return diff;
}


int get_sum_bf_min(int arr[], int arr_len)
{
	int sum = 0;
	int min = get_min(arr, arr_len);
	for (int i = 0; i <= arr_len; i++)
	{
		if (arr[i] != min){
			sum += arr[i];
		}else{
			break;
		}
	}
	return sum;
}
