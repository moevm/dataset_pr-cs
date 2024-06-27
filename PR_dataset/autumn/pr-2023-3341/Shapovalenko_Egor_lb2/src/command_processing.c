#include "command_processing.h"

void command_processing(int command,int array[],int size){
    switch(command){
		case 0:
		    print_answer(array[abs_max(array, size)]);
			break;
        case 1:
			print_answer(array[abs_min(array, size)]);
			break;
        case 2:
            print_answer(diff(array, size));
            break;
        case 3:
		    print_answer(sum(array, size));
			break;
        default:
            print_error();	
	}
}