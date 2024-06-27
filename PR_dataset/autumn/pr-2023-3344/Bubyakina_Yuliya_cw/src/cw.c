#include <stdio.h>
#include <locale.h>
#include "text.h"
#include "input.h"
#include "transliterate.h"
#include "print_special_symbols.h"
#include "replace_nums.h"
#include "delete_sentences_with_odd_numbers.h"
#include "repeat_sentences.h"

int main()
{
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.12, created by Bubyakina Yuliya.\n");

    int command = -1, repeat;
    wscanf(L"%d", &command);

    switch (command)
    {
    case 0:
    {
        Text *text = input();
        print_text(text);
        free_text(text);
        break;
    }
    case 1:
    {
        Text *text = input();
        transliterate(text);
        print_text(text);
        free_text(text);
        break;
    }
    case 2:
    {
        Text *text = input();
        print_special_symbols(text);
        free_text(text);
        break;
    }
    case 3:
    {
        Text *text = input();
        replace_nums(text);
        print_text(text);
        free_text(text);
        break;
    }
    case 4:
    {
        Text *text = input();
        delete_sentences_with_odd_numbers(text);
        print_text(text);
        free_text(text);
        break;
    }
    case 5:
    {
        wprintf(L"СПРАВКА\n");
        wprintf(L"\t0 - Вывод текста после первичной обязательной обработки(удаление повторно встречающихся предложений).\n");
        wprintf(L"\t1 - Транслитерация всех кириллических символов в тексте(ГОСТ 7.79-2000).\n");
        wprintf(L"\t2 - Вывод всех специальных символов для каждого предложения в порядке уменьшения их кода.\n");
        wprintf(L"\t3 - Замена всех цифр в тексте их двоичным кодом.\n");
        wprintf(L"\t4 - Удаление предложений, в которых есть нечётные цифры.\n");
        wprintf(L"\t5 - Справка.\n");
        break;
    }
    case 6:
    {
        Text *text = input();
        work_with_words_and_seps_text(text);
        free_text(text);
        break;
    }
    case 9:
    {
        Text *text = input();
        polindrom(text);
        free_text(text);
        break;
    }
    default:
        wprintf(L"Введена некорректная команда. Завершение работы.\n");
        break;
    }
}