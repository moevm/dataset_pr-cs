#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include "text.h"
#include "input_text.h"
#include "replace_digit.h"
#include "print_if_last_word_of_previous_sentence_is_in_current_sentence.h"
#include "sort_sentences.h"
#include "delete_sentence_if_len_is_less_than_2.h"
#include "function9.h"

int main()
{
    setlocale(LC_ALL, "");

    wprintf(L"Course work for option 5.16, created by Verdin Kirill.\n");

    int mode = -1;

    wscanf(L"%d\n", &mode);

    switch (mode)
    {
    case 0:
    {
        Text *txt = input_text();
        print_text(txt);
        free_text(txt);

        break;
    }
    case 1:
    {
        Text *txt = input_text();
        replace_digit_in_text(txt);
        print_text(txt);
        free_text(txt);

        break;
    }
    case 2:
    {
        Text *txt = input_text();
        print_sentences_if_last_word_of_previous_sentence_is_in_current_sentence(txt);
        free_text(txt);

        break;
    }
    case 3:
    {
        Text *txt = input_text();
        sort_sentences(txt);
        print_text(txt);
        free_text(txt);

        break;
    }
    case 4:
    {
        Text *txt = input_text();
        delete_sentence_if_len_is_less_than_2(txt);
        print_text(txt);
        free_text(txt);

        break;
    }
    case 5:
    {
        wprintf(L"Справка\n");
        wprintf(L"0 - вывести текст после первичной обработки;\n");
        wprintf(L"1 - зменить все слова заканчиващиеся на цифру так, чтобы они заканчивались на название этой цифры на кириллице;\n");
        wprintf(L"3 - отсортировать предложения по уменьшению количества слов в них;\n");
        wprintf(L"4 - удалить все предложения с 2 или меньше слов;\n");
        wprintf(L"5 - показать справку\n");
        break;
    }
    case 9:
    {
        wchar_t *str=malloc(500*sizeof(wchar_t));
        fgetws(str, 500, stdin);
        str[wcslen(str)-1]=L'\0';
        Text *txt = input_text();
        print_function9(txt, str);
        free_text(txt);
        free(str);
        break;
    }
    default:
        wprintf(L"Ошибка. Такой команды несуществует.\n");
        break;
    }

    return 0;
}