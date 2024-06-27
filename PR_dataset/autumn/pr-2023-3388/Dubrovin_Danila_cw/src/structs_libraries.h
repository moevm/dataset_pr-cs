#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>


#define START_BUFFER_SIZE 10
#define START_SENTENCES_COUNT 10
#define START_WORD_COUNT 10
#define FUNCTION_INFO L"0. - (do_basic_processing) Вывод текста после первичной обязательной обработки.\n1. - (convert_to_date) Для каждого предложения вывести строку-дату вида “ДД-ММ-ГГГГ”, где день - количество слов в предложении, месяц - наибольшая длина слова в предложении, год - общее количество символов в предложении + 1900.\n2. - (reverse_sentence) Вывести предложения так, чтобы слова шли в обратном порядке.\n3. - (sort_by_first_word) Отсортировать предложения по длине первого слова в предложении.\n4. - (delete_3_length_words) Удалить все предложения у которых все слова имеют длину не больше 3 символов.\n5. - Вывести информацию о функциях.\n"
#define COURSE_WORK_INFO L"Course work for option 5.8, created by Dubrovin Danila.\n"
#define ERROR_MEMORY_ALLOCATION L"Error: Не удалось выделить память.\n"
#define ERROR_read_text L"Error: Некорректный ввод.\n"
#define ERROR_COMMAND_NOT_FOUND L"Error: Несуществующая функция.\n"


struct Sentence
{
    wchar_t *sentence;
    wchar_t **words;
    size_t max_word_size;
    size_t count_of_words;
    size_t size_of_first_word;
};


struct Text
{
    wchar_t *input;
    size_t length;
    size_t sentences_count;
};
