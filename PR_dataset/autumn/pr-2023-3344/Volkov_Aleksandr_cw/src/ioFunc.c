#include "ioFunc.h"
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#define EXTRA_BUF 70

// Функция для чтения предложения из входного потока
struct Sentence readSentence() 
{
    struct Sentence end = {NULL, 0, 0};
    struct Sentence memory_error = {NULL, -1, -1};
    wchar_t *tmp = (wchar_t *)malloc(sizeof(wchar_t));
    wchar_t *sentence;
    // Проверка на возможность выделения памяти
    if (tmp) {
        sentence = tmp;
        tmp = NULL;
    }
    else {
        wprintf(L"Error: не удалось выделить память\n");
        return memory_error;
    }

    wchar_t c;
    int capacity = 1;
    int len = 0;
    wchar_t previous_c;
    while (c = getwchar()) {
        // Проверка на необходимость увеличения буфера
        if (len >= capacity) { 
            capacity += EXTRA_BUF;
            tmp = (wchar_t *)realloc(sentence, capacity * sizeof(wchar_t));
            if (tmp) { 
                sentence = tmp;
                tmp = NULL;
            }
            else {
                wprintf(L"Error: не удалось выделить память\n");
                free(sentence);
                return memory_error;
            }
        }

        if (c == L'.') {
        sentence[len] = L'\0';
        break;
    }

    if (c == L'\n' && previous_c == L'\n') {
        free(sentence);
        return end;
    }

    if (len >= 1 || c != L' ' && c != L'\t' && c != L'\n') // Удаление лишних символов в начале
        sentence[len++] = c;
    previous_c = c;

    }

    struct Sentence result = {sentence, len, capacity};
    return result;
}

// Функция для чтения текста
struct Text readText()
{
    struct Sentence *sent_list;
    struct Text error = {NULL, -1};
    struct Text blank = {NULL, 0};
    int count = 0;
    
    
    while (1) {
        // Вызов функции для чтения предложения
        struct Sentence str = readSentence(); 
         // Проверка на ошибку выделения памяти
        if (str.sentence == NULL && str.len == -1) {
            if (count != 0)
                free(sent_list);
            return error;     
        }
        // Проверка на пустое предложения
        if (str.sentence == NULL && str.len == 0) 
            break;
        
        // Проверка на первое предложение
        if (count == 0) {
            struct Sentence *tmp = (struct Sentence *)malloc((++count) * sizeof(struct Sentence));
            if (tmp == NULL)
                return error;
            sent_list = tmp;
            sent_list[count - 1] = str;
        } else {
            struct Sentence *tmp = (struct Sentence *)realloc(sent_list, (++count) * sizeof(struct Sentence));
            if (tmp == NULL)
                return error;
            sent_list = tmp;
            sent_list[count - 1] = str;
        }
    }
    // Проверка на пустой текст
    if (count == 0) 
        return blank;
    struct Text read_text = {sent_list, count};
    return read_text;
}

// Функция для удаления повторяющихся предложений
int removeRepeated(struct Text *text)
{
	int *tmp = (int *)calloc(text->count, sizeof(int));
	if (tmp == NULL)
		return -1;
	int *repeated_index = tmp;
	int unique_amount = 0; // Кол-во уникальных предложений
	int amount = text->count;
	for (int i = 0; i < amount; i++) {
		// Проверка на повторяющиеся предложения
        if (!repeated_index[i]) {
			for (int j = i + 1; j < amount; j++) {
				// Сравнение предложений без учёта регистра
                int flag = wcscasecmp(text->text[i].sentence, text->text[j].sentence);
				// Если раны, то помечаем 1
                if (flag == 0) repeated_index[j] = 1;
			}
            // В очередную ячейку записывается текущее предложение
			text->text[unique_amount++] = text->text[i];
		} else {
            // Если в трассировочном массиве стоит 1, то очищается выделенная память
			free(text->text[i].sentence);
		}
	}
	free(repeated_index);
    // Изначальный массив обрезается до размера unique_amount
	text->text = (struct Sentence *)realloc(text->text, unique_amount * sizeof(struct Sentence));
	text->count = unique_amount;
	return 0;
}

// Функция для вывода предложений на экран, каждое с новой строки
void printText(struct Text *text)
{
    for (int i = 0; i < text->count; i++) {
        if (text->text[i].len != 0)
            wprintf(L"%ls.\n", text->text[i].sentence);
    }
}

// Функция очищает память, выделенную под строки для хранения каждого
void freeText(struct Text *text)
{
    for (int i = 0; i < text->count; i++) {
        free(text->text[i].sentence);
    }
    free(text->text);
}
