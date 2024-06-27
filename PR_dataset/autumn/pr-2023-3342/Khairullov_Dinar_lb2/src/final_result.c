#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#include "console_input_opt.h"
#include "console_input_arr.h"
#include "final_result.h"
#define ARR_MAX_SIZE 20
#define STR_PRINT "%d\n"

int final_result(int case_num, int array[], int length){
    switch(case_num){
        case 0:
        	printf(STR_PRINT, index_first_negative(array, length));
        	break;

        case 1:
        	printf(STR_PRINT, index_last_negative(array, length));
        	break;

        case 2:
        	printf(STR_PRINT, multi_between_negative(array, length));
        	break;

        case 3:
        	printf(STR_PRINT, multi_before_and_after_negative(array, length));
        	break;

        default:
        	printf("Данные некорректны");
        	break;
    }
    return 0;
}
