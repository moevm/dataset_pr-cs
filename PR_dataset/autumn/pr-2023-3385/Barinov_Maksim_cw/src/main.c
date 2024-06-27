#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "func.h"
#include "InputOutput.h"
#include "Struct.h"

int check(struct Sentence* a) {
	wchar_t* x = calloc(a->size, sizeof(wchar_t));
	wchar_t* y = calloc(a->size, sizeof(wchar_t));
	int j = 0;
	for (int i = 0; i < a->size; i++) {
		if (iswalpha(a->symbols[i]) || iswdigit(a->symbols[i])) {
			x[j] = a->symbols[i];
			j++;
		}
	}
	//y = _wcsrev(x);
	for (int i = j - 1; i >= 0; i--) {
		y[j - 1 - i] = x[i];
	}
	if (wcscasecmp(x, y) == 0) {
		return 1;
	} else {
		return 0;
	}
}


void f(struct Text* text) {
	for (int i = 0; i < text->cnt; i++) {
		if (check(text->sents[i]) == 1) {
			OutSentence(text->sents[i]);
		}
	}
}



void solve() {
	struct Text* text;
	int k; wscanf(L"%d", &k);
	switch(k) {
		case 0:
			text = ReadText();	
			OutText(text);
			break;
		case 1:
			text = ReadText();
			translit_text(text);
			OutText(text);
			break;
		case 2:
			text = ReadText();
			search_special_char_text(text);
			OutText(text);
			break;
		case 3:	
			text = ReadText();
			translit_text_bin(text);
			OutText(text);
			break;
		case 4:
			text = ReadText();
			del_odd_sen(text);
			OutText(text);
			break;
		case 5:
			wprintf(L"\n================================\n");
			wprintf(L"Вывод справки о командах:\n");
			help();
			wprintf(L"================================\n");
			exit(0);
		case 9:
			text = ReadText();
			f(text);
			//OutText(text);
			break;
		default:
			wprintf(L"\n================================\n");
			wprintf(L"Error: введена неверная команда, программа будет завершена\n");
			wprintf(L"================================\n");
			exit(0);
	}
	freememory(text);
}

int main() {
	setlocale(LC_CTYPE, "");
	wprintf(L"Course work for option 5.12, created by Maksim Barinov\n");
	solve();
}
