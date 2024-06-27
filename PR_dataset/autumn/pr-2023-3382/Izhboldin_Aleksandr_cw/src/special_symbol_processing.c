#include "special_symbol_processing.h"

// Function 2
void change_special_symbols(int *err)
{
    if (*err) return;
    Text *text = Text_read(err);
    if (*err) return;
    text = basic_processing(text, err);
    if (*err) return;
    Text *new_text = Text_create(err);
    if (*err) return;
    Sentence *processed_sentence;
    for (size_t i = 0; i < text->size; ++i)
    {
        processed_sentence = Sentence_create(err);
        if (*err) return;
        for (size_t j = 0; j < text->sentences[i]->size; ++j)
        {
            if (wcschr(SPECIAL_SYMBOLS, text->sentences[i]->sentence[j]) != NULL &&
                text->sentences[i]->sentence[j] != L'\0')
            {
                Sentence_add_word(processed_sentence, STR_TO_REPLACE, err);
                if (*err) return;
            }
            else
            {
                Sentence_add_symbol(processed_sentence, text->sentences[i]->sentence[j], err);
                if (*err) return;
            }
        }
        Sentence_add_symbol(processed_sentence, L'\0', err);
        if (*err) return;
        Text_add_sentence(new_text, processed_sentence, err);
        if (*err) return;
    }

    Text_print(new_text);

    Text_delete(&text);
    Text_delete(&new_text);
}