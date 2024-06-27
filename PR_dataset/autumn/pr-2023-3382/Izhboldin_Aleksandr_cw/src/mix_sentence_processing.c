#include "mix_sentence_processing.h"

// Function 4
void delete_mixed_sentence(int *err)
{
    if (*err) return;
    Text *text = Text_read(err);
    if (*err) return;
    text = basic_processing(text, err);
    if (*err) return;
    for (size_t i = 0; i < text->size; ++i)
        if (!check_sentence_if_mixed(text->sentences[i], err))
            Sentence_delete(&text->sentences[i]);

    text = Text_recreate(text, err);
    if (*err) return;
    Text_print(text);
    Text_delete(&text);
}

bool check_sentence_if_mixed(Sentence *sentence, int *err)
{
    if (sentence == NULL) return NULL;
    if (*err) return NULL;

    Sentence *sentence_copy = Sentence_copy(sentence, err);
    if (*err) return NULL;
    wchar_t *buffer;
    wchar_t *split = wcstok(sentence_copy->sentence, DELIMITERS, &buffer);
    while (split != NULL)
    {
        if (check_word_if_mixed(split))
        {
            Sentence_delete(&sentence_copy);
            return false;
        }

        split = wcstok(NULL, DELIMITERS, &buffer);
    }
    Sentence_delete(&sentence_copy);
    return true;
}

// Return true if mixed otherwise false
bool check_word_if_mixed(wchar_t *word)
{
    bool eng_symbol = false;
    bool ru_symbol = false;
    for (size_t i = 0; i < wcslen(word); ++i)
    {
        if (iswalpha(word[i]))
        {
            if (!eng_symbol && word[i] < 128)
                eng_symbol = true;
            else if (!ru_symbol && ((word[i] >= 1040 && word[i] <= 1103) || (word[i] == 1025 || word[i] == 1105)))
                ru_symbol = true;
        }
        if (ru_symbol && eng_symbol)
            return true;
    }
    return false;
}