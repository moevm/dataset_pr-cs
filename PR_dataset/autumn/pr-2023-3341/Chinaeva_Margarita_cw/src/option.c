#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#include "preprocessing.h"
#include "palindrome.h"
#include "replace_special_symbol.h"
#include "sort_latin.h"
#include "delete_cyrillic_latin.h"
#include "list_option.h"

#include "structs.h"
#include "input.h"
#include "output.h"
#include "free_memory.h"


int get_option(void) {
    int option;
    wscanf(L"%d%*c", &option);
    return option;
}

int option_exsist(int option) {
    if (option <= 5 && option >= 0 || option == 9 ) {
        return 1;
    }
    else {
        return 0;
    }
}

void print_words_from_entered_letters(){
    wchar_t slovo[10000];
    wchar_t new_symbol = getwchar();
    int t = 0;
    while (new_symbol != '\n') {
        slovo[t] = towlower(new_symbol);
        t++;
        new_symbol = getwchar();
    }
    slovo[t] = L'\0';
    Text* text = (Text*)malloc(sizeof(Text));
    text->sentences = (Sentence*)malloc(sizeof(Sentence));
    input_text(text);
    for (int i = 0; i < text->size_text; i++){
        const wchar_t separators[] = L" ,.";
        wchar_t* ptr;
        wchar_t* token = wcstok(text->sentences[i].str, separators, &ptr);
        while (token != NULL) {
            int check_all=0;
            int check_sl=0;
            for (int k=0; k < wcslen(token);k++) {
                if (wcschr(slovo, towlower(token[k]))){
                    check_sl++;
                }
                check_all++;
            }
            if (check_all==check_sl) {
                wprintf(L"%ls\n", token);
            }
            token = wcstok(NULL, separators, &ptr);
        }
    }
}

void running_option(int option) {
    switch (option)
    {
    case 0:
        preprocessing();
        break;
    case 1:
        palindrome();
        break;
    case 2:
        replace_special_symbol();
        break;
    case 3:
        sort_latin();
        break;
    case 4:
        delete_cyrillic_latin();
        break;
    case 5:
        list_option();
        break;
    case 9:
        print_words_from_entered_letters();
    }
}
