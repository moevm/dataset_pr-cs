#include"Structs.h"
#include"SortByLatin.h"
#include<stdlib.h>
#define LATIN_ALPHABET L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
int compare_by_latin_count(const void* a, const void* b)
{
    const struct Sentence* first = (const struct Sentence*)a;
    const struct Sentence* second = (const struct Sentence*)b;
    if (first->latin_letters_count < second->latin_letters_count)
    {
        return 1;
    }
    if (first->latin_letters_count > second->latin_letters_count)
    {
        return -1;
    }
    return  0;
}

struct Text sort_by_latin(struct Text text)
{
    wchar_t latin_alphabet[54] = LATIN_ALPHABET;
    for (int i = 0; i < text.sentences_count; ++i)
    {
        int latin_letters_cnt = 0;
        for (int j = 0; j < text.sentences[i].words_count; ++j)
        {
            for (int k = 0; k < text.sentences[i].words[j].letters_count; ++k)
            {
                int is_in_alphabet = 0;

                for (int l = 0; l < 54; ++l)
                {
                    if (text.sentences[i].words[j].letters[k] == latin_alphabet[l])
                    {
                        is_in_alphabet = 1;
                        break;
                    }
                }
                if (is_in_alphabet)
                {
                    latin_letters_cnt++;
                }
            }
        }
        text.sentences[i].latin_letters_count = latin_letters_cnt;

    }
    qsort(text.sentences, text.sentences_count, sizeof(struct Sentence), compare_by_latin_count);


    return text;
}