#include"ChangeSym.h"
#include"RemoveSentences.h"
#include"SortByLatin.h"
#include"UniqueWordsCount.h"
#include"Structs.h"
#include"Input.h"
#include"Outputs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>




struct Text big_word_replace(struct Text text,int max_word_size)
{


    for (size_t i = 0; i < text.sentences_count; i++)
    {
        for (size_t j = 0; j < text.sentences[i].words_count; j++)
        {


            if (text.sentences[i].words[j].letters_count > max_word_size)
            {

                wchar_t sep = text.sentences[i].words[j].letters[text.sentences[i].words[j].letters_count-1];

                if (sep == L',' || sep == '.') {
                    if (text.sentences[i].words[j].letters_count - 1 <= max_word_size) {
                        break;
                    }
                }
                wchar_t* big_word = (wchar_t*) malloc(20*sizeof(wchar_t));

                if (sep == L'.') {
                    wchar_t *temp_word = L"(большое слово).";
                    wcscpy(big_word, temp_word);
                } else if (sep == L',') {
                    wchar_t *tempWord = L"(большое слово),";
                    wcscpy(big_word, temp_word);
                } else
                {
                    wchar_t *tempWord = L"(большое слово)";
                    wcscpy(big_word, temp_word);
                }



                free(text.sentences[i].words[j].letters);
                text.sentences[i].words[j].letters = big_word;

            }
        }

    }
    return text;
}

void free_memory(struct Text text)
{
    for (int i = 0; i < text.sentences_count; i++) {
        for (int j = 0; j < text.sentences[i].words_count; j++) {
            free(text.sentences[i].words[j].letters);
        }
        free(text.sentences[i].words);
    }
    free(text.sentences);
}

int menu(struct Text text, int operation_number)
{
    int is_need_clear = 1;
    switch (operation_number) {
        case 0:
            output(text);
            break;

        case 1: {
            int unique_words_count;
            struct Unique_Word* unique_words;

            unique_words = unique_words_count(text, &unique_words_count);

            for (int i = 0; i < unique_words_count; ++i) {
                wprintf(L"%ls - %d\n", unique_words[i].letters, unique_words[i].words_count);
                free(unique_words[i].letters);
            }
            free(unique_words);

            break;
        }
        case 2:
            text = change_sym(text);
            output(text);
            break;
        case 3:
            text = sort_by_latin(text);
            output(text);
            break;
        case 4:
            text = remove_sentences(text);
            output(text);
            break;
        case 9:
        {
            text = big_word_replace(text,max_word_len);
            output(text);
            break;
        }
        case 5:
            setlocale(LC_CTYPE, "");
            inquiry_output();
            is_need_clear = 0;
            break;
        default:
            setlocale(LC_CTYPE, " ");
            wprintf(L"\tError: <некорректный номер операции>");
            break;
    }
}

void print_work_info()
{
    wprintf(L"Course work for option 5.5, created by Konstantin Pushko.\n");

}

int main()
{
    int operation_number;

    int max_word_len;

    setlocale(LC_CTYPE, "");
    
    print_work_info();

    if (input_args(&operation_number,&max_word_len))
    {
        struct Text text = input_text();
    }

     if(menu(text,operation_number))
     {
         free_memory(text);
     }




}
