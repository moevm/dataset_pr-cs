#define NUMS_ARR_LENGTH 100
#define STR_TO_READ_SIZE 1000

#include <stdlib.h>
#include <stdio.h>

int reverse_num(int num, int negative_num, int zero_ending_num) {

	float num_clone = num;
	int new_num = 0;
	int digits_counter = 0;
	while (num_clone >= 1) {
		num_clone /= 10;
		digits_counter++;

	}
	for (int i = 0; i < digits_counter; i++) {

		int digits_place = num % 10;
		int power_index = 1;
		num /= 10;
		for (int j = 1; j < digits_counter - i; j++) {
			power_index *= 10;
		}
		new_num += digits_place * power_index;
	}
	for (int g = 0; g < zero_ending_num; g++) {
		new_num *= 10;
	}
	zero_ending_num = -1;

	if (negative_num) {
		return new_num * (-1);
	}
	return new_num;
}

int index_first_even(int arr[NUMS_ARR_LENGTH], int l) {
	for (int i = 0; i < l; i++) {

		if (arr[i] % 2 == 0) {

			return i;
		}
	}

}

int index_last_odd(int arr[NUMS_ARR_LENGTH], int l) {
	int last_ind = 0;

	for (int i = 0; i < l; i++) {
		if (abs(arr[i]) % 2 == 1) {
			last_ind = i;

		}
	}
	return last_ind;
}

int sum_between_even_odd(int arr[NUMS_ARR_LENGTH], int l) {
	int sum = 0;
	for (int i = index_first_even(arr, l); i < index_last_odd(arr, l); i++) {
		sum += abs(arr[i]);
	}
	return sum;
}

int sum_before_even_and_after_odd(int arr[NUMS_ARR_LENGTH], int l) {
	int sum = 0;
	for (int i = 0; i < l; i++) {
		sum += abs(arr[i]);
	}
	return sum - sum_between_even_odd(arr, l);
}
int main() {
	int nums[NUMS_ARR_LENGTH];
	char string[STR_TO_READ_SIZE];
	fgets(string, STR_TO_READ_SIZE, stdin);
	int pow_index = 1, new_num = 0, negative_num = 0, zero_ending_num = -1, new_num_index = 0;
	int program_mode = string[0] - '0';
	for (int i = 2; i < STR_TO_READ_SIZE; i++) {

		if ((string[i] != ' ') && (string[i] != '\n') && (string[i] != '-')) {

			new_num += (string[i] - '0') * pow_index;
			pow_index *= 10;
			if (string[i] == '0') {
				zero_ending_num += 1;
			}
			else {
				zero_ending_num = 0;
			}

		}
		else if (string[i] == '-') {
			negative_num = 1;
		}
		else if (string[i] == '\n') {
			nums[new_num_index] = reverse_num(new_num, negative_num, zero_ending_num);
			new_num_index++;
			break;
		}
		else {
			nums[new_num_index] = reverse_num(new_num, negative_num, zero_ending_num);
			new_num_index++;
			if (negative_num) {
				negative_num = 0;
			}
			pow_index = 1;
			new_num = 0;
		}
	}


	switch (program_mode) {
	case(0):
		printf("%d", index_first_even(nums, new_num_index));
		break;
	case(1):
		printf("%d", index_last_odd(nums, new_num_index));
		break;
	case(2):
		printf("%d", sum_between_even_odd(nums, new_num_index));
		break;
	case(3):
		printf("%d", sum_before_even_and_after_odd(nums, new_num_index));
		break;
	default:
		printf("%s", "Данные некорректны");
	}


	return 0;
}
