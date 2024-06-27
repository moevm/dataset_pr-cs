#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_before_and_after_negative.h"
#include "multi_between_negative.h"
#include "switch_function.h"

void switch_function(int key, int *array, int length)
{
    switch(key)
	{
		case 0:
            printf("%d", index_first_negative(array, length));
			break;
		case 1:
            printf("%d", index_last_negative(array, length));
            break;
		case 2:
			printf("%d", multi_between_negative(array, length));
			break;
		case 3:
            printf("%d", multi_before_and_after_negative(array, length));
			break;
		default:
		    printf("Данные некорректны");
		    break;
	}
}
