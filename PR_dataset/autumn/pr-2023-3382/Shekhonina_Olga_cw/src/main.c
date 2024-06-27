#include "readtext.h"
#include "functions_13.h"
#include "free_memory.h"
#include "print_text.h"
#include "functions_24.h"

void change_sentences(Text* text) {
    wchar_t* word = find_first_word(text->pr_sent[0]);
    int len_word = wcslen(word);
    wchar_t* replace_word = L"(большое слово)";
    for(int i = 0; i<text->count_sent; i++) {
        int len_buffer = 0;
        for(int j = 0; j<text->pr_sent[i]->len_sent; j++) {
            if(text->pr_sent[i]->sentence[j] == L' ' || text->pr_sent[i]->sentence[j] == L'.' || text->pr_sent[i]->sentence[j] == L',') {
                if(len_buffer>len_word) {
                    wchar_t* pr_str = text->pr_sent[i]->sentence + j -len_buffer;
		    wchar_t* new_sent = malloc(1000*sizeof(wchar_t));
                    wcsncpy(new_sent, text->pr_sent[i]->sentence, text->pr_sent[i]->len_sent-wcslen(pr_str));
                    wcscat(new_sent, replace_word);
                    wcscat(new_sent, pr_str+len_buffer);
                    text->pr_sent[i]->len_sent = text->pr_sent[i]->len_sent - len_buffer + 15;
		    free(text->pr_sent[i]->sentence);
		    text->pr_sent[i]->sentence = malloc(2*text->pr_sent[i]->len_sent*sizeof(wchar_t));
		    wcscpy(text->pr_sent[i]->sentence, new_sent);
		    free(new_sent);
                }
                len_buffer = 0;
            } else {
                len_buffer++;
            }
        }
    }
}

int main()
{   setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.15, created by Olga Shekhonina.\n");
    int number;
    wchar_t c;
    wscanf(L"%d%c", &number, &c);
    if(number == 0) {
        Text* text = readtext();
        delete_repeat_sentence(text);
        print_text(text);
        free_memory(text);
    } 
    else if(number == 1) {
        Text* text = readtext();
        delete_repeat_sentence(text);
        replace_highnoon_and_midnight(text);
        print_text(text);
        free_memory(text);
    }
    else if(number == 2) {
	Text* text = readtext();
	delete_repeat_sentence(text);
	print_text(text);
	wprintf(L"\n");
	find_dates(text);
	sort_dates(text);
	output_sorted_dates(text);
	free_memory(text);
    }
    else if(number == 3) {
        Text* text = readtext();
        delete_repeat_sentence(text);
        remove_some_sentences(text);
        print_text(text);
        free_memory(text);
    }
    else if(number == 4) {
	Text* text = readtext();
	delete_repeat_sentence(text);
	print_text(text);
	wprintf(L"\n");
	find_dates(text);
	did_dates_happen(text);
	free_memory(text);
    }
    else if(number == 5) {
	wprintf(L"Программа реализует несколько функций, которые вызываются командами: числа от 0 до 4.\n\n0 - Первичная обработка текста(удаление табуляции в начале предложений, удаление повторяющихся предложений).\n1 - Замена в тексте всех подстрок “high noon” на “полдень” и “полночь” на “midnight”.\n2 - Вывод всех дат в тексте заданных в виде “ DD/MM/YYYY ” или “ YYYY-MM-DD ” в порядке возрастания этих дат. \n3 - Удаление всех предложения, которые начинаются и заканчиваются на одно и то же слово.\n4 - Для всех вхождений дат в тексте вида “<day> <month> <year>, вывод этих дат в виде “DD.MM.YYYY” и строки “Happened” если эта дата была до текущей и “Not Happened” в противном случае.");
    }
    else if(number == 9) {
	Text* text = readtext();
	change_sentences(text);
        print_text(text);
	//free_memory(text);
    }	
    else {
        wprintf(L"Данные некорректны.\n");
    }
    return 0;
}