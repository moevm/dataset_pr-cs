#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int [], int);
int index_last_zero(int [], int);
int sumbetween(int [], int);
int sum_before_and_after(int [], int);

int index_first_zero(int arr[], int n){
	for (int i=0; i<n; i++){
		if (arr[i] == 0) return i;
	}
	return -1;
}

int index_last_zero(int arr[], int n){
        for (int i=n-1; i>=0; i--){
                if (arr[i] == 0) return i;
        }
        return -1;
}

int sum_between(int arr[], int n){
	int sum = 0;
	int first = index_first_zero(arr, n) + 1;
	int last = index_last_zero(arr, n);

	for (int i = first; i < last; i++) sum += abs(arr[i]);

	return sum;
}

int sum_before_and_after(int arr[], int n){
	int sum = 0;
        int first = index_first_zero(arr, n);
        int last = index_last_zero(arr, n);

	for (int i = 0; i <= first; i++) sum += abs(arr[i]);
	for (int i = last; i < n; i++) sum += abs(arr[i]);
	
	return sum;
}

int main(){
	int arr[100];
	int j = 0, operation, n;
	
	do{
		if (j) scanf("%d", &arr[j - 1]);
		else scanf("%d", &operation);
		j++;
	} while (getchar() != '\n');
	
	n = j - 1;

	

	switch (operation) {
		case 0: 
			if (index_first_zero(arr, n) == -1)
			       	printf("Данные некорректны\n");
			else
				printf("%d\n", index_first_zero(arr, n));
			break;
		case 1:
			if (index_last_zero(arr, n) == -1)
                                printf("Данные некорректны\n");
                        else
                                printf("%d\n", index_last_zero(arr, n));
                        break;
		case 2:
			printf("%d\n", sum_between(arr, n));
			break;
		case 3:
			printf("%d\n", sum_before_and_after(arr, n));
			break;
		default:
			printf("Данные некорректны\n");

	}
	return 0;
}
