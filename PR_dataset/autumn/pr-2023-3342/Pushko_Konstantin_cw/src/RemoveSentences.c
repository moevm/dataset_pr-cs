#include"Structs.h"
#include"RemoveSentences.h"
#include<stdlib.h>
#define CAPITAL_ALPHABET L"ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
struct Text remove_sentences(struct Text text)
{
    int special_sym_codes[5] = { 35, 36, 94, 37, 64 };
    wchar_t capital_alphabet[62] = CAPITAL_ALPHABET;
    int sentence_number = 0;
    while (sentence_number < text.sentences_count)
    {
        int is_capital_letter = 0;
        int is_special_sym = 0;
        for (int j = 0; j < text.sentences[sentence_number].words_count; ++j)
        {
            for (int i = 0; i < text.sentences[sentence_number].words[j].letters_count; ++i)
            {
                for (int k = 0; k < 62; ++k)
                {
                    if ((int)text.sentences[sentence_number].words[j].letters[i] == (int)capital_alphabet[k])
                    {
                        is_capital_letter = 1;
                        break;
                    }
                }

                for (int k = 0; k < 5; ++k)
                {
                    if ((int)text.sentences[sentence_number].words[j].letters[i] == special_sym_codes[k])
                    {
                        is_special_sym = 1;
                        break;
                    }
                }
            }
        }
        if (!is_capital_letter && is_special_sym)
        {
            for (int j = 0; j < text.sentences[sentence_number].words_count - 1; j++)
            {
                free(text.sentences[sentence_number].words[j].letters);
            }
            free(text.sentences[sentence_number].words);
            for (int i = sentence_number; i < text.sentences_count; ++i)
            {
                text.sentences[i].words = text.sentences[i + 1].words;
                text.sentences[i].words_count = text.sentences[i + 1].words_count;
            }


            text.sentences_count--;
            sentence_number--;
        }
        sentence_number++;
    }


    return text;
}