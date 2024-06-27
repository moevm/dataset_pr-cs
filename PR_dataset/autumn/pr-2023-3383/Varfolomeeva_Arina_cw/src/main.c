#include "print_t.h"
#include "read_t.h"
#include "print_help.h"
#include "del_duplicates.h"
#include "first_func.h"
#include "second_func.h"
#include "third_func.h"
#include "fourth_func.h"
#include "free_t.h"
#include "struct.h"

int main() {
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.6, created by Arina Varfolomeeva.\n");
    int command_number;
    wscanf(L"%d", &command_number);
    if (command_number == 5) {
    	print_help();
    	return 0;
    }
    Text text = read_t();
    if (text.length == 0) {
    	wprintf(L"Error: there is no text.\n");
    	return 0;
    }
    switch(command_number) {
    	case 0:
    		text = del_duplicates(text);
    		print_t(text);
    		free_t(text);
		break;
    	case 1:
    		first_func(text);
    		free_t(text);
    		break;
    	case 2:
    		text = del_duplicates(text);	
    		text = second_func(text);
    		print_t(text);
    		free_t(text);
    		break;
    	case 3:
    		text = del_duplicates(text);
    		text = third_func(text);
    		print_t(text);
    		free_t(text);
    		break;
    	case 4:
    		text = del_duplicates(text);
    		text = fourth_func(text);
    		print_t(text);
    		free_t(text);
    		break;
    	default:
    		wprintf(L"Error: there is no such command.\n");
    		free_t(text);
    }
    return 0;
}
