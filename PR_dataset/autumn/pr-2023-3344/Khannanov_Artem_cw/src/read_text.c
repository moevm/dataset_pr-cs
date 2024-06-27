#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "read_text.h"
#include "structs.h"
#include "is_single_sentence.h"
#include "memory_error.h"


struct Text read_text()
{
    setlocale(LC_ALL, "");

    //Определение основных переменных
    struct Text input_text;
    struct Sentence new_sentence;

    size_t new_line = 0; // Подсчитывает количество идущих подряд "\n"
    size_t is_sentence = 0; // Проверка, находится ли символ внутри предложения
    size_t length = 0; // Счёт длины строки
    size_t is_memory_ok = 1;

    new_sentence.sentence = (wchar_t *)malloc(sizeof(wchar_t));
    if (new_sentence.sentence == NULL) memory_error(is_memory_ok, L"read_text.c sentence");

    input_text.text = (struct Sentence *)malloc(sizeof(struct Sentence));
    input_text.count = 0;
    input_text.is_memory_ok = 1;
    if (input_text.text == NULL) memory_error(is_memory_ok, L"read_text.c text");

    wchar_t letter;
    //--------------------

    if (is_memory_ok == 0) input_text.is_memory_ok = 0;
    
    //Считывание входный данных
    while (is_memory_ok)
    {   
        letter = getwchar();

        if (!iswspace(letter)) is_sentence = 1; // Проверка на начало предложения

        if (is_sentence) // Условие выполняется только внутри предложения
        {
            // Добавление символов в слово и увеличение размера массива
            new_sentence.sentence[length++] = letter;
            new_sentence.sentence = (wchar_t *)realloc(new_sentence.sentence, sizeof(wchar_t) * (length + 1));

            if (new_sentence.sentence == NULL) memory_error(is_memory_ok, L"read_text.c sentence");
            //--------------------

            if (letter == L'.') // Выполняется при конце предложения
            {
                // Замыкание предложения
                new_sentence.sentence[length++] = L'\n';
                new_sentence.sentence = (wchar_t *)realloc(new_sentence.sentence, sizeof(wchar_t) * (length + 1));

                if (new_sentence.sentence == NULL) memory_error(is_memory_ok, L"read_text.c sentence");

                new_sentence.sentence[length] = L'\0';
                //--------------------

                // Запись предложения в текст и увеличение размера массива текста
                if (is_single_sentence(input_text, new_sentence))
                {
                    input_text.text[input_text.count++] = new_sentence;
                    input_text.text = (struct Sentence *)realloc(input_text.text, sizeof(struct Sentence) * (input_text.count + 1));

                    if (input_text.text == NULL) memory_error(is_memory_ok, L"read_text.c text");
                }
                //--------------------

                // Обнуление переменных
                is_sentence = 0;
                length = 0;
                new_sentence.sentence = (wchar_t *)malloc(sizeof(wchar_t));

                if (new_sentence.sentence == NULL) memory_error(is_memory_ok, L"read_text.c sentence");
                //--------------------
            }
        }

        // Проверка на окончание ввода текста
        if (letter == L'\n')
        {
            new_line++;
            if (new_line == 2) 
            {
                if (is_sentence == 1)
                {
                    new_sentence.sentence[length - 2] = L'.';
                    if (new_sentence.sentence == NULL) memory_error(is_memory_ok, L"read_text.c sentence");
                    new_sentence.sentence[length - 1] = L'\n';
                    new_sentence.sentence[length] = L'\0';
                    
                    if (is_single_sentence(input_text, new_sentence))
                    {
                        input_text.text[input_text.count++] = new_sentence;
                        input_text.text = (struct Sentence *)realloc(input_text.text, sizeof(struct Sentence) * (input_text.count + 1));

                        if (input_text.text == NULL) memory_error(is_memory_ok, L"read_text.c text");
                    }

                    new_sentence.sentence = (wchar_t *)malloc(sizeof(wchar_t));
                    is_sentence = 0;
                }
                break;
            }
        }
        else
        {
            new_line = 0;
        }
    }
    //--------------------

    // Освобождение памяти
    free(new_sentence.sentence);
    //--------------------

    return input_text;
}