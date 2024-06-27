#include "select_func.h"

void num_scan(){
        int numb_of_func;
        wscanf(L"%d",&numb_of_func);
        choice_func(numb_of_func);
}

void choice_func(int n){
	switch(n){
		case 0:
			text_print(read_text());
			break;
		case 1:
			all_transliteration(read_text());
			break;
		case 2:
			all_special_sym(read_text());
			break;
		case 3:
			all_bin_sym(read_text());
			break;
		case 4:
			all_delete_odd(read_text());
			break;
		case 5:
			wprintf(FUNC_INFO);
			num_scan();
			break;
		default:
			wprintf(L"Error: Wrong number of function\n");
			break;
	}
}
