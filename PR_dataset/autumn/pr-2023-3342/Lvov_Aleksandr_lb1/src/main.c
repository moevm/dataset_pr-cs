#include <stdio.h>
#define MAX_SIZE 100

int max(int arr[], int arr_size);
int min(int arr[], int arr_size);
int diff(int arr[], int arr_size);
int sum(int arr[], int arr_size);


int main(){
	int index = 0;
	int arr[MAX_SIZE];
	char space = ' ';
	int num_case;
	
	scanf("%d", &num_case);

	while (index < MAX_SIZE && space ==  ' '){
		scanf("%d%c", &arr[index], &space);
		index++;
	}
	
	int size = index;

	switch(num_case) 
	{
		case 0:
		printf("%d\n", max(arr, size));
		break;

		case 1:
		printf("%d\n", min(arr, size));
		break;

		case 2:
		printf("%d\n", diff(arr, size));
		break;

		case 3:
		printf("%d\n", sum(arr, size));
		break;

		default:
		printf("Данные некорректны");
	}

	return 0;
}

int max(int arr[], int arr_size){
        int result = arr[0];
        for (int i = 1; i < arr_size; i++){
                if (arr[i] >= result)
                {
                        result = arr[i];
                }
        }
        return result;
}

int min(int arr[], int arr_size){
        int result = arr[0];
        for (int i = 1; i < arr_size; i++){
                if (arr[i] <= result){
                        result = arr[i];
                }
        }
        return result;
}

int diff(int arr[], int arr_size){
        int result = max(arr, arr_size) - min(arr, arr_size);
        return result;
}

int sum(int arr[], int arr_size){
        int min_elem = min(arr, arr_size);
        int result = 0;
        for (int i = 0; i < arr_size; i++)
        {
                if (arr[i] == min_elem)
                {
                        break;
                }
                else
                {
                        result += arr[i];
                }
        }

        return result;
}