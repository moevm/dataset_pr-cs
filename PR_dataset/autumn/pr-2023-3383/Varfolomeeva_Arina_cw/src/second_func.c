#include "second_func.h"
#include "struct.h"

int is_number(wchar_t *str){
	for (int i = 0; i < wcslen(str); i++) {
		if (!iswdigit(str[i])) {
			return 0;
		}	
	}
	return 1;
}

wchar_t *is_month(wchar_t *word) {
	wchar_t months[][12] = {L"января", L"февраля", L"марта", L"апреля", L"мая", L"июня", L"июля", L"августа", L"сентября", L"октября", L"ноября", L"декабря"};
	int number_month = 0;
	wchar_t *answer;
	for (int i = 0; i<12; i++) {
		if (!wcscasecmp(word, months[i])) {
			number_month = i+1;
			if (number_month == 1) {
				answer = L"01";	
			}
			if (number_month == 2) {
				answer = L"02";	
			}
			if (number_month == 3) {
				answer = L"03";	
			}
			if (number_month == 4) {
				answer = L"04";	
			}
			if (number_month == 5) {
				answer = L"05";	
			}
			if (number_month == 6) {
				answer = L"06";	
			}
			if (number_month == 7) {
				answer = L"07";	
			}
			if (number_month == 8) {
				answer = L"08";	
			}
			if (number_month == 9) {
				answer = L"09";	
			}
			if (number_month == 10) {
				answer = L"10";	
			}
			if (number_month == 11) {
				answer = L"11";	
			}
			if (number_month == 12) {
				answer = L"12";	
			}
			break;
		}
	}
	if (number_month != 0) {
		return answer;	
	}
	return 0;
}

Sentence *change_date(Sentence *sentence) {
	int index = sentence->length-8;
	int count_words = 0;
	wchar_t **all_words = (wchar_t **)malloc(sentence->length * sizeof(wchar_t *));
	wchar_t *ptr;
	wchar_t *token;
	wchar_t *year;
	wchar_t *day;
	wchar_t *month;
	int count_symb_month;
	wchar_t *new_date = (wchar_t *)malloc(11 * sizeof(wchar_t));
	wchar_t* sentence_copy = malloc(sizeof(wchar_t) * (sentence->length+1));
	wcsncpy(sentence_copy, sentence->string, sentence->length);
	sentence_copy[sentence->length] = 0;
	token = wcstok(sentence_copy, L" ", &ptr); 
	while (token != NULL) {
		all_words[count_words] = token;
		count_words++;
		token = wcstok(NULL, L" ", &ptr); 
	}
	if (wcslen(all_words[count_words-2]) == 4 && is_number(all_words[count_words-2])) {
		year = all_words[count_words-2];
		if (is_month(all_words[count_words-3])) {
			month = is_month(all_words[count_words-3]);
			
			count_symb_month = wcslen(all_words[count_words-3]);
		} else return sentence;
		if (is_number(all_words[count_words-4])) {
			day = all_words[count_words-4];		
		} else return sentence;
	} else return sentence;
	index -= count_symb_month;
	sentence->string[index++] = L'/';
	sentence->string[index++] = month[0];
	sentence->string[index++] = month[1];
	sentence->string[index++] = L'/';
	sentence->string[index++] = year[0];
	sentence->string[index++] = year[1];
	sentence->string[index++] = year[2];
	sentence->string[index++] = year[3];
	sentence->string[index++] = L'.';
	sentence->string[index] = L'\0';
	return sentence;
}

Text second_func(Text txt) {
	for (int i = 0; i < txt.length; i++) {
		if (wcsstr(txt.text[i]->string, L"г.") != NULL) {
    			txt.text[i] = change_date(txt.text[i]);
    		}
    	}
	return txt;
}
