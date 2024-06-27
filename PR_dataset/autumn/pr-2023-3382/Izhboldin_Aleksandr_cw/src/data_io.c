#include "data_io.h"

Sentence *Sentence_read(bool *end, int *err)
{
    if (*err) return NULL;
    Sentence *sentence = Sentence_create(err);
    if (*err) return NULL;

    wchar_t symbol, prev_symbol;
    bool first_word_found = false;
    while (true)
    {
        prev_symbol = symbol;
        symbol = getwchar();

        if (symbol == EOF)
        {
            *end = true;
            Sentence_delete(&sentence);
            return NULL;
        }

        if (prev_symbol == L'\n' && symbol == prev_symbol) // if "\n\n" found
        {
            *end = true;
            if (first_word_found) // was word before
            {
                Sentence_replace_symbol(sentence, sentence->size - 1, L'.', err);
                if (*err) return NULL;
                Sentence_add_symbol(sentence, L'\0', err);
                if (*err) return NULL;
                return sentence;
            } else // wasn't word before
            {
                Sentence_delete(&sentence);
                return NULL;
            }
        }

        // Skip all spaces before first word
        if (first_word_found || !iswspace(symbol))
        {
            Sentence_add_symbol(sentence, symbol, err);
            if (*err) return NULL;
            if (!iswspace(symbol))
                first_word_found = true;
        }

        // End sentence
        if (symbol == L'.')
        {
            Sentence_add_symbol(sentence, L'\0', err);
            if (*err) return NULL;
            break;
        }
    }

    return sentence;
}



// Read all text from stdin and return pointer to Text structure
Text *Text_read(int *err)
{
    if (*err) return NULL;
    Text *text = Text_create(err);
    if (*err) return NULL;
    Sentence *sentence;
    bool end = false;
    while (true)
    {
        sentence = Sentence_read(&end, err);
        if (*err) return NULL;
        if (sentence != NULL)
        {
            Text_add_sentence(text, sentence, err);
            if (*err) return NULL;
            if (end) break;
        }
        else break;
    }
    return text;
}

// Printing text to stdout, ignore NULL sentences
void Text_print(Text *text)
{
    if (text == NULL) return;
    for (size_t i = 0; i < text->size; ++i)
        if (text->sentences[i] != NULL)
            wprintf(L"%ls\n", text->sentences[i]->sentence);
}
