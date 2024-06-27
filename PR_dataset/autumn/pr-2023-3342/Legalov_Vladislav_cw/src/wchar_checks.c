#include "wchar_checks.h"


int is_alpha_upper_ru_en(wchar_t ch){
	return (isupper(ch) || (ch >= L'А' && ch <= L'Я') || (ch == L'Ё'));
}

wchar_t to_lower_ru_en(wchar_t ch){
	ch = tolower(ch);
	if (ch >= L'А' && ch <= L'Я')
		ch = ch - L'А' + L'а';
	return ch;
}

int check_wchars_equality(wchar_t first, wchar_t second){
	return (to_lower_ru_en(first) == to_lower_ru_en(second));
}

void get_next_alpha(wchar_t source, wchar_t *res_first, wchar_t *res_second){
	static wchar_t special_cases[] = L"деёжзДЕЁЖЗ";
	wchar_t *ptr = NULL;
	if ((ptr = wcschr(special_cases, source)) && (((ptr - special_cases) % 5) < 3)) {
		*res_first = ptr[1]; 
		*res_second = ptr[2];
	 } else
	if (source >= L'a' && source <= L'z'){
		*res_first = L'a' + ((source - L'a') + 1) % 26;
		*res_second = L'a' + ((source - L'a') + 2) % 26;
	} else
	if (source >= L'A' && source <= L'Z'){
		*res_first = L'A' + ((source - L'A') + 1) % 26;
		*res_second = L'A' + ((source - L'A') + 2) % 26;
	} else
	if (source >= L'а' && source <= L'я'){
		*res_first = L'а' + ((source - L'а') + 1) % 32;
		*res_second = L'а' + ((source - L'а') + 2) % 32;
	} else
	if (source >= L'А' && source <= L'Я'){
		*res_first = L'А' + ((source - L'А') + 1) % 32;
		*res_second = L'А' + ((source - L'А') + 2) % 32;
	}
}




