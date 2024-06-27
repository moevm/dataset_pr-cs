#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include "text.h"
#include "get_text.h"
#include "replace_non_alfa_chars.h"
#include "print_number_of_occurences_of_all_words.h"
#include "sort_sentences_by_english_letter_count.h"
#include "delete_sentences_that_have_special_chars_and_no_uppercase_letters.h"
#include "replace_words.h"

int main()
{
    setlocale(LC_ALL, "");

    wprintf(L"Course work for option 5.5, created by Danila Zhavoronok.\n");

    int mode = -1;
    wscanf(L"%d", &mode);
    getwchar();
    switch (mode)
    {
    case 0:
    {
        text *text = get_text();
        print_text(text);
        free_text(text);

        break;
    }
    case 1:
    {
        text *text = get_text();
        print_number_of_occurences_of_all_words(text);
        free_text(text);

        break;
    }
    case 2:
    {
        text *text = get_text();
        replace_non_alfa_chars_text(text);
        print_text(text);
        free_text(text);

        break;
    }
    case 3:
    {
        text *text = get_text();
        sort_sentences_by_english_letter_count(text);
        print_text(text);
        free_text(text);

        break;
    }
    case 4:
    {
        text *text = get_text();
        delete_sentences_that_have_special_chars_and_no_uppercase_letters(text);
        print_text(text);
        free_text(text);

        break;
    }
    case 5:
    {
        wprintf(L"СПРАВКА\n");
        wprintf(L"\t0 - Вывод текста после первичной обязательной обработки.\n");
        wprintf(L"\t1 - Распечатать каждое слово (с учётом регистра) и количество его повторений в тексте.\n");
        wprintf(L"\t2 - Заменить каждый символ, который не является буквой, на его код.\n");
        wprintf(L"\t3 - Отсортировать предложения по количеству латинских букв в предложении.\n");
        wprintf(L"\t4 - Удалить все предложения, которые содержат специальные символы и не содержат заглавные буквы.\n");
        wprintf(L"\t5 - Показать эту справку.\n");

        break;
    }

    case 9:
    {
        wchar_t* word = (wchar_t*)malloc(sizeof(wchar_t)*100);
        fgetws(word, 100, stdin);
        text *text = get_text();
        replace_words(text, wcslen(word)-1);
        print_text(text);
        free_text(text);

        break;
    }

    default:
    {
        wprintf(L"Введена нераспознанная команда, выход.\n");
        break;
    }
    }

    return 0;
}
