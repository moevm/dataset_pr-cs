#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "structs.h"
#include "read_text.h"
#include "compare_multiply.h"
#include "check_digits_and_symbs.h"
#include "find_single_words.h"
#include "find_dates.h"


int main()
{
    setlocale(LC_ALL, "");

    wprintf(L"Course work for option 5.6, created by Artem Khannanov.\n");

    int code = 6;
    int is_code_scanned = wscanf(L"%d", &code);

    if (is_code_scanned) // Проверка на считывание числа
    {
        if (code == 5)
        {
            wprintf(L"Справка:\n"); // Вывод справки о функциях программы
            wprintf(L"1 Функция - Распечатать каждое слово которое встречается не более одного раза в тексте.\n");
            wprintf(L"2 Функция - Каждую подстроку в тексте имеющую вид “<день> <месяц> <год> г.” заменить на подстроку вида “ДД/ММ/ГГГГ”.\nНапример, подстрока “20 апреля 1889 г.” должна быть заменена на “20/04/1889”.\n");
            wprintf(L"3 Функция - Отсортировать предложения по произведению длин слов в предложении.\n");
            wprintf(L"4 Функция - Удалить все предложения, которые содержат символ ‘#’ или ‘№’, но не содержат ни одной цифры.\n");
        }
        else if (code < 5 && code >= 0)
        {
            struct Text text = read_text(); // Вызов чтения входного текста

            if (text.is_memory_ok == 1)
            {
                switch (code)
                {
                case 0:
                    // Вывод обработанного текста
                    for (size_t i = 0; i < text.count; i++)
                    {
                        wprintf(L"%ls", text.text[i].sentence);
                    }
                    //--------------------
                    break;

                case 1:
                    find_single_words(text); // Нахождение слов, встречающихся в тексте один раз
                    
                    break;

                case 2:
                    find_dates(text); // Поиск и замена дат на формат “ДД/ММ/ГГГГ”.

                    for (int i = 0; i < text.count; i++)
                    {
                        wprintf(L"%ls", text.text[i].sentence);
                    }
                    break;

                case 3:
                    qsort(text.text, text.count, sizeof(struct Sentence), compare_multiply); // Сортировка предложений по произведению длин слов

                    // Вывод обработанного текста
                    for (int i = 0; i < text.count; i++)
                    {
                        wprintf(L"%ls", text.text[i].sentence);
                    }
                    //--------------------

                    break;

                case 4:
                    for (size_t i = 0; i < text.count; i++) // Поиск и удаление предложений, в которых нет цифр, но есть №, #
                    {
                        if (check_digits_and_symbs(text.text[i])) wprintf(L"%ls", text.text[i].sentence);
                    }
                    break;

                default:
                    wprintf(L"Error: введено некорректное число\n");
                    break;
                }

                for (size_t i = 0; i < text.count; i++) // Освобождение памяти
                {
                    free(text.text[i].sentence);
                }
                free(text.text);
            }
        }
        else
        {
            wprintf(L"Error: введено некорректное число\n");
        }
    }
    else
    {
        wprintf(L"Error: неверный формат данных\n");
    }


    return 0;
}
