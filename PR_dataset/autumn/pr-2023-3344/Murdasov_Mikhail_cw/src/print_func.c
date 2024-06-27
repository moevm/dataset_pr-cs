#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#include "structures.h"

void print_text(struct Text* text){
    for(int i = 0; i < text->len; i++){
        if(text->sentences[i]->sentence != NULL){
            wprintf(L"%ls.\n", text->sentences[i]->sentence);
        }
    }
    for(int i = 0; i < text->len; i++){
        free(text->sentences[i]->sentence);
        free(text->sentences[i]);
    }
}

void README(){
    wprintf(L"************************************************************************\n");
    wprintf(L"-------------Справка о функциях, реализованных в программе--------------\n\n");
    wprintf(L"0 – вывод текста после первичной обязательной обработки\n");
    wprintf(L"1 – сдвиг слов в предложениях на положительное число N\n");
    wprintf(L"2 – вывод всех уникальных кириллических и латинских символов в тексте\n");
    wprintf(L"3 – подсчет и вывод количества слов длина которых равна 1, 2, 3 и т.д.\n");
    wprintf(L"4 – удаление всех слов, оканчивающихся на заглавный символ\n");
    wprintf(L"5 – вывод справки о функциях, которые реализует программа\n");
    wprintf(L"9 – замена больших слов\n");
    wprintf(L"************************************************************************\n");

}

void print_error(wchar_t* error){
    fwprintf(stderr, L"\033[1;31m\[ERROR]:\033[0m \033[3;31m %ls \033[0m\n", error);
    exit(1);
}
