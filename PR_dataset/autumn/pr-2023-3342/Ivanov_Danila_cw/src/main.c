#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "reading.h"
#include "delete.h"
#include "memory.h"
#include "function_sum_of_minutes.h"
#include "function_sort.h"
#include "function_of_replace_symbols.h"
#include "function_of_delete_sentences.h"
#include "reference.h"
#include "structs.h"
#include "function_print_some_sentences.h"

void output(struct Text text){
    for (int i = 0; i < text.count_of_sentences; i++){
        wprintf(L"%ls\n", text.list_of_sentences[i].sentence);
        free(text.list_of_sentences[i].sentence);
    }
}

void make_massive_of_words(struct Text text){
    for (int i = 0; i < text.count_of_sentences; i++){
        struct Sentence sent = text.list_of_sentences[i];
        wchar_t* str = sent.sentence;
        wchar_t* word = calloc(wcslen(str), sizeof(wchar_t));
        wchar_t** words = malloc(sizeof(wchar_t*));
        int index = 0;
        int len = 0;
        for (int x = 0; x < wcslen(str); x++){
            if (str[x] == L' ' || str[x] == L'.' || str[x] == L',' || str[x] == L'\n' || str[x] == L'\t'){
                if (index > 0){
                    words[len++] = word;
                    word = calloc(wcslen(str), sizeof(wchar_t));
                    index = 0;
                    words = realloc(words, (len + 1) * sizeof(wchar_t*));
                }
            }
            else{
                word[index++] = str[x];
            }
        }
        text.list_of_sentences[i].count_of_words = len;
        text.list_of_sentences[i].list_of_words = words;
    }
}

struct Text filling_of_struct(struct Text text, int* ptr_len, wchar_t** dynamic_strs){
    text.count_of_sentences = (*ptr_len);
    for (int i = 0; i < (*ptr_len); i++){
        struct Sentence sen;
        sen.sentence = space(dynamic_strs[i]); // удаление пробельных символов в начале предложения
        sen.len_of_sentence = wcslen(dynamic_strs[i]);
        (text.list_of_sentences)[i] = sen;
    }
    text.count_of_sentences = (*ptr_len);
    return text;
}

int main()
{
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.14, created by Danila Ivanov.\n");
    int num_of_func;
    wscanf(L"%ld", &num_of_func); // считывание номера функции

    wchar_t* first_str = malloc(sizeof(wchar_t));

    if (num_of_func == 9){
        wcscpy(first_str, input_of_ninth_function(first_str));
    }

    // ошибка при вводе неверного номера
    if (!(num_of_func == 0 || num_of_func == 1 || num_of_func == 2 || num_of_func == 3 || num_of_func == 4 || num_of_func == 5 || num_of_func == 9)){
        wprintf(L"Error: <неверный номер функции>\n");
        return 0;
    }

    // вызов функции под номером 5
    if (num_of_func == 5){
        print_reference();
        return 0;
    }
    else {
        // выделение динамической памяти для хранения текста
        wchar_t **dynamic_strs = allocate_memory_for_text();

        int index = 0;
        int* ptr_index = &index;

        int len = 0;
        int* ptr_len = &len;

        // чтение текста и его сохранение в динамический массив
        dynamic_strs = reading_of_sentences(ptr_index, ptr_len, dynamic_strs);

        // создание структуры
        struct Text text = {0, malloc((*ptr_len) * sizeof(struct Sentence))};
        text = filling_of_struct(text, ptr_len, dynamic_strs);

        // удаление повторяющихся предложений
        text = delete_sentences(text);

        // разбиение предложения на слова
        make_massive_of_words(text);

        // вызов функции под номером 0
        if (num_of_func == 0){
            output(text);
        }

        // вызов функции под номером 1
        if (num_of_func == 1){
            wprintf(L"%d\n", func_sum_of_minutes(text));
        }

        // вызов функции под номером 2
        if (num_of_func == 2){
            qsort(text.list_of_sentences, text.count_of_sentences, sizeof(struct Sentence), cmp);
            output(text);
        }

        // вызов функции под номером 3
        if (num_of_func == 3){
            for (int i = 0; i < text.count_of_sentences; i++){
                text.list_of_sentences[i] = func_of_replace_symbols(text.list_of_sentences[i]);
            }
            output(text);
        }

        // вызов функции под номером 4
        if (num_of_func == 4){
            text = func_of_delete_sentences(text);
            output(text);
        }

        if (num_of_func == 9){
            int lent = 0;
            int* ptr_lent = &lent;
            wchar_t** words = massive(first_str, ptr_lent);
            text = func_print_some_sentences(text, words, ptr_lent);
            output(text);
        }

        // освобождение памяти
        free_memory(dynamic_strs, text.count_of_sentences);
        free(text.list_of_sentences);
        return 0;
    }
}
