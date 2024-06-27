#include <stdio.h>
#include <stdlib.h>
#define STR_SIZE 101
#define pair arr, arr_len
int index_first_zero(int arr[], int arr_len);
int index_last_zero(int arr[], int arr_len);
int sum_between(int arr[], int arr_len);
int sum_before_and_after(int arr[], int arr_len);
int main() {
	int str[STR_SIZE];
	int str_len = 0;
	char space;
	while (space != '\n') {
		scanf("%d%c", &str[str_len], &space);
		str_len++;
	}
	int task = str[0];
	int arr_len = str_len - 1;
	int arr[100];
	for (int i = 0; i < str_len; i++ ) {
        arr[i] = str[i+1];
	}
	switch(task) {
	case 0: {
	    printf("%d\n", index_first_zero(pair));
	    break;
    }
	case 1: {
	    printf("%d\n", index_last_zero(pair));
	    break;
	}
	case 2: {
	    printf("%d\n", sum_between(pair));
	    break;
	}
	case 3: {
	    printf("%d\n", sum_before_and_after(pair));
	    break;
	}
	default: {
	    printf("Данные некорректны");
	    break;
    }
    }
	return 0;
}
int index_first_zero(int arr[], int arr_len) {
    int number;
    for (int i=0; i < arr_len; i++) {
        if (arr[i] == 0) {
            number = i;
            break;
        }
    }
    return number;
}
int index_last_zero(int arr[], int arr_len) {
    int number;
    for (int i=0; i < arr_len; i++) {
        if (arr[i] == 0) {
            number = i;
        }
    }
    return number;
}
int sum_between(int arr[], int arr_len) {
    int sum = 0;
    int f_zero = index_first_zero(pair);
    int l_zero = index_last_zero(pair);
    int i = f_zero + 1;
    while (i < l_zero) {
        sum += abs(arr[i]);
        i++;
    }
    return sum;
}
int sum_before_and_after(int arr[], int arr_len) {
    int sum = 0;
    int f_zero = index_first_zero(pair);
    int l_zero = index_last_zero(pair);
    for (int i = 0; i < f_zero; i++) {
        sum += abs(arr[i]);
    }
    for (int i = l_zero; i < arr_len ; i++) {
        sum += abs(arr[i]);
    }
    return sum;
}
