#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "replace_word.h"
#include "read_text.h"
#include "structures.h"
#include "replace_digits.h"
#include "check_cyrillic.h"
#include "print_words.h"
#include "sort_sentence.h"
#include "change_sentence_order.h"
#include "begin.h"
int main(void) {
    setlocale(LC_ALL, "");
    int option;
    option = begin();
    struct Text* text = malloc(sizeof(struct Text));
    if (text==NULL){
        wprintf(L"Error: failed to allocate memory for structure Text [function: main]\n");
        exit(1);
    }
    wchar_t ch;
    wchar_t* word = malloc(sizeof(wchar_t));
    int len = 0;
    switch (option) {
        case 0:
            read_text(text);
            for (size_t i = 0;i<text->len;i++){
                wprintf(L"%ls.\n",text->text[i]->sentence);
            }
            break;
        case 1:
            read_text(text);
            print_words(text);
            break;
        case 2:
            read_text(text);
            replace_digits(text);
            break;
        case 3:
            read_text(text);
            sort_sentence(text);
            break;
        case 4:
            read_text(text);
            change_sentence_order(text);
            break;
        case 5:
            wprintf(L"1 опция - Распечатать каждое слово (с учетом регистра), которое встречается минимум три раза в тексте, а также количество вхождений каждого такого слова в текст.\n2 опция - Заменить каждый символ цифры на число вхождений данной цифры во всем тексте.\n3 опция - Отсортировать слова в предложениях по уменьшению количеству латинских букв в словах.\n4 опция - Поменять порядок слов на обратный в предложениях, которые состоят только из кириллических букв.\n");
            break;
        case 9:
            ch = getwchar();
            while (ch!='\n'){
                word = realloc(word,sizeof(wchar_t)*(len+2));
                word[len++] = ch;
                ch = getwchar();
            }
            word[len] = L'\0';
            read_text(text);
            replace_word(text,word);
            break;
        default:
            wprintf(L"Incorrect option number. Please, enter number from 0 to 5\n");
            wprintf(L"Program finished\n");
            break;
    }
    return 0;
}