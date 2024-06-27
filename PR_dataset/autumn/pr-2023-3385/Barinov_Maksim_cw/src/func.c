#include "func.h"

void help() {
	wprintf(L"Справка о командах:\n\
	0 - Вывод текста после удаления повторяющихся предложений\n\
	1 - Сделать транслитерацию всех кириллических символов в тексте.\n\
	2 - Для каждого предложения вывести все специальные символы (№*$#@) в порядке уменьшения их кода.\n\
	3 - Заменить все цифры в тексте их двоичным кодом.\n\
	4 - Удалить все предложения в которых есть нечетные цифры.\n");
}

void freememory(struct Text* text) {
	for (size_t i = 0; i < text->cnt; i++) {
		free(text->sents[i]);	
	}
	free(text);
}

void delSentence(struct Text* text, int id) { // id номер предложения при индексации с 0
	for (size_t i = id; i < text->cnt - 1; i++) { 
		text->sents[i]->symbols = text->sents[i + 1]->symbols;
		text->sents[i]->size = text->sents[i + 1]->size;
		text->sents[i]->ends = text->sents[i + 1]->ends;
	}
	free(text->sents[text->cnt - 1]);
	text->cnt--;
}

void delDuplicate(struct Text* text) {
	for (size_t i = 0; i < text->cnt; i++) {
		for (size_t j = i + 1; j < text->cnt; j++) {
			if (wcscasecmp(text->sents[i]->symbols, text->sents[j]->symbols) == 0) {
				delSentence(text, j);
			}
		}
	}	
}

// 1 задача
int translit_char(wchar_t * str, int i, int size) { // 1 -заменили 1 буквой 2 - двумя 3 - тремя
    setlocale(LC_CTYPE, "");
    wchar_t tmp = str[i];
    switch (towlower(tmp)) {
        case L'а':
            if (iswupper(tmp)) {
                str[i] = L'A';
            } else {
                str[i] = L'a';
            }
            return 1;
        case L'б':
            if (iswupper(tmp)) {
                str[i] = L'B';
            } else {
                str[i] = L'b';
            }
            return 1;
        case L'в':
            if (iswupper(tmp)) {
                str[i] = L'V';
            } else {
                str[i] = L'v';
            }
            return 1;
        case L'г':
            if (iswupper(tmp)) {
                str[i] = L'G';
            } else {
                str[i] = L'g';
            }
            return 1;
        case L'д':
            if (iswupper(tmp)) {
                str[i] = L'D';
            } else {
                str[i] = L'd';
            }
            return 1;
        case L'е':
            if (iswupper(tmp)) {
                str[i] = L'E';
            } else {
                str[i] = L'e';
            }
            return 1;
        case L'ё':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'Y';
                str[i + 1] = L'o';
            } else {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'y';
                str[i + 1] = L'o';
            }
            return 2;
        case L'ж':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'Z';
                str[i + 1] = L'h';
            } else {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'z';
                str[i + 1] = L'h';
            }
            return 2;
        case L'з':
            if (iswupper(tmp)) {
                str[i] = L'Z';
            } else {
                str[i] = L'z';
            }
            return 1;
        case L'и':
            if (iswupper(tmp)) {
                str[i] = L'I';
            } else {
                str[i] = L'i';
            }
            return 1;
        case L'й':
            if (iswupper(tmp)) {
                str[i] = L'J';
            } else {
                str[i] = L'j';
            }
            return 1;
        case L'к':
            if (iswupper(tmp)) {
                str[i] = L'K';
            } else {
                str[i] = L'k';
            }
            return 1;
        case L'л':
            if (iswupper(tmp)) {
                str[i] = L'L';
            } else {
                str[i] = L'l';
            }
            return 1;
        case L'м':
            if (iswupper(tmp)) {
                str[i] = L'M';
            } else {
                str[i] = L'm';
            }
            return 1;
        case L'н':
            if (iswupper(tmp)) {
                str[i] = L'N';
            } else {
                str[i] = L'n';
            }
            return 1;
        case L'о':
            if (iswupper(tmp)) {
                str[i] = L'O';
            } else {
                str[i] = L'o';
            }
            return 1;
        case L'п':
            if (iswupper(tmp)) {
                str[i] = L'P';
            } else {
                str[i] = L'p';
            }
            return 1;
        case L'р':
            if (iswupper(tmp)) {
                str[i] = L'R';
            } else {
                str[i] = L'r';
            }
            return 1;
        case L'с':
            if (iswupper(tmp)) {
                str[i] = L'S';
            } else {
                str[i] = L's';
            }
            return 1;
        case L'т':
            if (iswupper(tmp)) {
                str[i] = L'T';
            } else {
                str[i] = L't';
            }
            return 1;
        case L'у':
            if (iswupper(tmp)) {
                str[i] = L'U';
            } else {
                str[i] = L'u';
            }
            return 1;
        case L'ф':
            if (iswupper(tmp)) {
                str[i] = L'F';
            } else {
                str[i] = L'f';
            }
            return 1;
        case L'х':
            if (iswupper(tmp)) {
                str[i] = L'X';
            } else {
                str[i] = L'x';
            }
            return 1;
        case L'ц':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'C';
                str[i + 1] = L'z';
            } else {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'c';
                str[i + 1] = L'z';
            }
            return 2;
        case L'ч':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'C';
                str[i + 1] = L'h';
            } else {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'c';
                str[i + 1] = L'h';
            }
            return 2;
        case L'ш':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'S';
                str[i + 1] = L'h';
            } else {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L's';
                str[i + 1] = L'h';
            }
            return 2;
        case L'щ':
            if (iswupper(tmp)) {
                wmemmove(str + i + 2, str + i, (size - i + 1));
                str[i] = L'S';
                str[i + 1] = L'h';
                str[i + 2] = L'h';
            } else {
                wmemmove(str + i + 2, str + i, (size - i + 1));
                str[i] = L's';
                str[i + 1] = L'h';
                str[i + 2] = L'h';
            }
            return 3;
        case L'ъ':
            wmemmove(str + i + 1, str + i, size - i + 1);
            str[i] = L'`';
            str[i + 1] = L'`';
            return 2;
        case L'ы':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i,  (size - i + 1));
                str[i] = L'Y';
                str[i + 1] = L'`';
            } else {
                wmemmove(str + i + 1, str + i, (size - i + 1));
                str[i] = L'y';
                str[i + 1] = L'`';

            }
            return 2;
        case L'ь':
            str[i] = 39;
            return 1;
        case L'э':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'E';
                str[i + 1] = L'`';
            } else {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'e';
                str[i + 1] = L'`';

            }
            return 2;
        case L'ю':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'Y';
                str[i + 1] = L'u';
            } else {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'y';
                str[i + 1] = L'u';

            }
            return 2;
        case L'я':
            if (iswupper(tmp)) {
                wmemmove(str + i + 1, str + i, size - i + 1);
                str[i] = L'Y';
                str[i + 1] = L'a';
            } else {
                wmemmove(str + i + 1, str + i, size - i + 1); 
                str[i] = L'y';
                str[i + 1] = L'a';
            }
            return 2;
        default:
            return 1;
    }
}

int len_translit_char(struct Sentence* a, int i) {
	wchar_t len2[] = L"ёжцчшыэюяъ";
	if (wcschr(len2, a->symbols[i]))return 2;
	if (a->symbols[i] == L'щ') return 3;
	return 1;
}

int translit_sentence(struct Sentence* a){
	for (size_t i = 0; i < a->size;) {
		if (iswalpha(a->symbols[i])) {
			int len = len_translit_char(a, i);
			a->symbols = (wchar_t*)realloc(a->symbols, sizeof(wchar_t) * a->size +sizeof(wchar_t)*(len + 3));
			if (a->symbols == NULL) {
				wprintf(L"Error: не удалось сделать транслитерацию");
				return 1;	
			}
			int k = translit_char(a->symbols, i, a->size);
			a->size += k - 1;
			i += k;
		} else {
			i++;
		}
	}
	return 0;
}


void translit_text(struct Text* text) {
	for (size_t i = 0; i < text->cnt;i++) {
		if (translit_sentence(text->sents[i])) {
			freememory(text);
			exit(0);
		}
	}
}

// 2 задача
struct Sentence* search_special_char(struct Sentence* a) {
	wchar_t k[] = L"№*$#@";
	wchar_t* s = (wchar_t*) malloc(sizeof(wchar_t) * size_block);
	int len = 0, size = size_block;
	for (size_t i = 0; i < a->size; i++) {
		if (wcschr(k, a->symbols[i]) != NULL) {
			if (len + 1 >= size) {
				s =  (wchar_t*) realloc(s, (i + 1) * sizeof(wchar_t) + size_block * sizeof(wchar_t));
				if (s == NULL) {
					wprintf(L"Error: Не удалось выделить память");
					free(s);
					exit(0);
				}
				size += size_block;
			}
			s[len] = a->symbols[i];
			len++;
		}
	}
	struct Sentence* sentens = (struct Sentence*) malloc(sizeof(struct Sentence*));
	sentens->symbols = s;
	sentens->size = len;
	return sentens;
}

int comp_special_char(const void* a, const void* b) {
	return *(wchar_t*) b - *(wchar_t*) a;
}

struct Text* search_special_char_text(struct Text* text) {
	for (size_t i = 0; i < text-> cnt; i++) {
		struct Sentence* a = search_special_char(text->sents[i]);
		qsort(a->symbols, a->size, sizeof(wchar_t), (int(*) (const void *, const void *)) comp_special_char);
		text->sents[i] = a;
	}
}

//3 задача
int translit_dig(wchar_t *str, int i, int size) {
    switch ((str[i] - L'0')) {
        case 0:
            str[i] = L'0';
            return 1;
        case 1:
            str[i] = L'1';
            return 1;
        case 2:
            wmemmove(str + i + 1, str + i, size - i + 1);
            str[i] = L'1';
            str[i + 1] = L'0';
            return 2;
        case 3:
            wmemmove(str + i + 1, str + i, size - i + 1);
            str[i] = L'1';
            str[i + 1] = L'1';
            return 2;
        case 4:
            wmemmove(str + i + 2, str + i, size - i + 1);
            str[i] = L'1';
            str[i + 1] = L'0';
            str[i + 2] = L'0';
            return 3;
        case 5:
            wmemmove(str + i + 2, str + i, size - i + 1);
            str[i] = L'1';
            str[i + 1] = L'0';
            str[i + 2] = L'1';
            return 3;
        case 6:
            wmemmove(str + i + 2, str + i, size - i + 1);
            str[i] = L'1';
            str[i + 1] = L'1';
            str[i + 2] = L'0';
            return 3;
        case 7:
            wmemmove(str + i + 2, str + i, size - i + 1);
            str[i] = L'1';
            str[i + 1] = L'1';
            str[i + 2] = L'1';
            return 3;
        case 8:
            wmemmove(str + i + 3, str + i, size - i + 1);
            str[i] = L'1';
            str[i + 1] = L'0';
            str[i + 2] = L'0';
            str[i + 3] = L'0';
            return 4;
        case 9:
            wmemmove(str + i + 3, str + i, size - i + 1);
            str[i] = L'1';
            str[i + 1] = L'0';
            str[i + 2] = L'0';
            str[i + 3] = L'1';
            return 4;
    }
}

int len_bin(struct Sentence* a, int i) {
	int k = (a->symbols[i] - L'0');
	int l[] = {1, 1, 2, 2, 3, 3, 3, 3, 4, 4};
	return l[k];
}

int translit_sentence_dig(struct Sentence* a) {
	for (size_t i = 0; i < a->size;) {
		if (iswdigit(a->symbols[i])) {
			int len = len_bin(a, i);
			a->symbols = (wchar_t*)realloc(a->symbols, sizeof(wchar_t) * a->size +sizeof(wchar_t)*(len));
			if (a->symbols == NULL) {
				wprintf(L"Error: не удалось сделать транслитерацию");
				return 1;	
			}
			int k = translit_dig(a->symbols, i, a->size);
			a->size += k - 1;
			i += k;
		} else {
			i++;
		}
	}
	return 0;
}

void translit_text_bin(struct Text* text) {
	for (size_t i = 0; i < text->cnt;i++) {
		if (translit_sentence_dig(text->sents[i])) {
			freememory(text);
			exit(0);
		}
	}
}

//4 задача
int odd_sen(struct Sentence* a) {
	for (size_t i = 0; i < a->size; i++) {
		if (iswdigit(a->symbols[i])) {
			if ((a->symbols[i] - L'0')&1) return 1;
		}
	}
	return 0;
}

void del_odd_sen(struct Text* text) {
	for (size_t i = 0; i < text->cnt;) {
		if (odd_sen(text->sents[i])) {
			delSentence(text, i);
		} else {
			i++;
		}
	}
}

