
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Func_index_first_even.h"
#include "Func_index_last_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "sum_between_even_odd.h"





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
