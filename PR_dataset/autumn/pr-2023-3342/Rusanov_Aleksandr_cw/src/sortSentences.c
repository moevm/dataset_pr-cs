#include "sortSentences.h"separator

int get_last_word_length(Sentence sentence)
{
    int start_index = 0;
    int end_index = 0;
    int check = 0;
    for (int index = sentence.size - 1; index >= 0; index--)
    {
        if ((check == 0) && !is_separator(sentence.string[index]))
        {
            check = 1;
            end_index = index;
        }
        if ((check == 1) && is_separator(sentence.string[index]))
        {
            start_index = index;
            break;
        }
    }
    return end_index - start_index;
}

int compare_sentences_by_last_word_length(const void *a, const void *b)
{
    Sentence *sentence_a = (Sentence *)a;
    Sentence *sentence_b = (Sentence *)b;

    int last_word_len_a = get_last_word_length(*sentence_a);
    int last_word_len_b = get_last_word_length(*sentence_b);

    return last_word_len_a - last_word_len_b;
}

void sort_text_by_last_word_length(Text text)
{
    qsort(text.sentences, text.size, sizeof(Sentence), compare_sentences_by_last_word_length);
}
