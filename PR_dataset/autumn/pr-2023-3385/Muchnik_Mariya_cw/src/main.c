#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "struct.h"
#include "print_error.h"
#include "print_help.h"
#include "get_text.h"
#include "print_text.h"
#include "get_minutes.h"
#include "sort_sentences.h"
#include "replace_symbols.h"
#include "delete_sentences.h"
#include "check_words.h"
#include "free_all.h"

int main(){
	setlocale(LC_CTYPE, "");
	wprintf(L"Course work for option 5.14, created by Mariya Muchnik.\n");

	int n = 13;

	struct Text text;
	
	wchar_t c = getwchar();

	if (iswdigit(c)) n = (int)c-48;
	
	switch(n){
		case 0:
			text = get_text();
			print_text(text);
			free_all(text);
			break;
		case 1:
            text = get_text();
			get_minutes(text);
			free_all(text);
			break;
		case 2:
            text = get_text();
			sort_sentences(text);
			print_text(text);
			free_all(text);
			break;
		case 3:
            text = get_text();
			replace_symbols(text);
			print_text(text);
			free_all(text);
			break;
		case 4:
            text = get_text();
			text = delete_sentences(text);
			print_text(text);
			free_all(text);
			break;
		case 5:
			print_help();
			break;
		case 9:
			text = get_text();
			check_words(text);
			free_all(text);
			break;
		default:
			print_error(L"Неккоретный номер команды");
			break;
	}

	return 0;
}
