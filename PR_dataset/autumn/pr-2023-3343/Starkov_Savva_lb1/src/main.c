
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int sum_before_even_and_after_odd(int* massive, int count_number_massive);
int sum_between_evenodd(int *massive, int count_number_massive);
int Func_index_last_odd(int *massive_int, int count_number_massive);
int Func_index_first_even(int *massive_int, int count_number_massive);
//кейсы в отдельные функции надо выделить

int main()
{
	int number_solution;
	int massive_int[100] = {0};
	int count_number_massive = 0;
	scanf("%d", &number_solution);
	while (getchar() != '\n') {
		scanf("%d", &massive_int[count_number_massive]);
		count_number_massive++;
	}

	// int index_last_odd = Func_index_last_odd(massive_int, count_number_massive);
	// int index_first_even = Func_index_first_even(massive_int, count_number_massive);
	// int sumafter = sum_before_even_and_after_odd(massive_int, index_first_even, index_last_odd, count_number_massive);
	// int sumeven = sum_between_evenodd(massive_int, index_first_even, index_last_odd);

	switch (number_solution)
	{
	    case 0:
		//index_first_even
		// Func_index_first_even(massive_int, count_number_massive)
			printf("%d", Func_index_first_even(massive_int, count_number_massive));
			break;
		//index_first_even


	    case 1:
		//index_last_odd
			printf("%d", Func_index_last_odd(massive_int, count_number_massive));
			break;
        case 2:

            printf("%d", sum_between_evenodd(massive_int, count_number_massive));
            break;
        case 3:
            printf("%d", sum_before_even_and_after_odd(massive_int, count_number_massive));
			break;
        default:
        	printf("Данные некорректны");
        	break;

    }
	return 0;
}

int Func_index_first_even(int* massive_int, int count_number_massive)
{
	int index_iterator = 0;
	while (index_iterator < count_number_massive) {
		if (massive_int[index_iterator] % 2 == 0) {
			return index_iterator;
		}
		else {
			index_iterator++;
		}
	}

}

int Func_index_last_odd(int* massive_int, int count_number_massive) {
	int index_iterator = count_number_massive;
	while (index_iterator > 0) {
		if (massive_int[index_iterator] % 2 != 0) {
			return index_iterator;
		}
		else {
			index_iterator--;
		}
	}
	return index_iterator;
}

int sum_between_evenodd(int* massive, int count_number_massive) {
	int iterator = Func_index_first_even(massive,count_number_massive);
	int summ_abs = 0;
	for (iterator; iterator < Func_index_last_odd(massive,count_number_massive); iterator++) {
		summ_abs = abs(massive[iterator]) + summ_abs;
	}
	return summ_abs;

}

int sum_before_even_and_after_odd(int* massive, int count_number_massive) {
	int iterator = 0;
	int summ_abs_first = 0;
	int summ_abs_second = 0;
	int number_fisrt_even = Func_index_first_even(massive,count_number_massive);
	int number_last_odd = Func_index_last_odd(massive, count_number_massive);
	for (iterator;iterator < number_fisrt_even ;iterator++)
	{
		summ_abs_first+= abs(massive[iterator]);
	}
	for (int iterator2 = count_number_massive;iterator2 != number_last_odd-1;iterator2--){
		summ_abs_second+= abs(massive[iterator2]);
	}
	return summ_abs_first + summ_abs_second;
}
