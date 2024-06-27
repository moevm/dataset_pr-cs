#include "transliterate.h"
#include "sentence.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>

Text *create_text()
{
    Text *text = (Text *)malloc(sizeof(Text));
    text->cap = 4;
    text->len = 0;
    text->sentences = (Sentence **)malloc(text->cap * sizeof(Sentence *));
    return text;
}

void extend_text(Text *text)
{
    if (text->len < text->cap - 1)
        return;
    text->cap += 4;
    text->sentences = (Sentence **)realloc((text->sentences), text->cap * sizeof(Sentence *));
}

void free_text(Text *text)
{
    for (int i = 0; i < text->len; i++)
    {
        free_sentence(text->sentences[i]);
    }
    free(text);
}

void push_text(Text *text, Sentence *sentence)
{
    text->len++;
    extend_text(text);
    text->sentences[text->len - 1] = sentence;
}

void print_text(Text *text)
{
    for (int i = 0; i < text->len; i++)
    {
        // replace_n_at_index_sentence(text->sentences[i], L"HOLA", 8, 0);
        print_sentence(text->sentences[i]);
    }
}
void work_with_words_and_seps_sentence(Sentence *sentence)
{
    Text *words = create_text();
    Text *seps = create_text();

    Sentence *copy = create_sentence();
    push_sentence(copy, sentence->chars);

    wchar_t *ch;
    wchar_t *current_word = wcstok(copy->chars, L", ", &ch);
    while (current_word != NULL)
    {

        Sentence *word = create_sentence();
        push_sentence(word, current_word);
        push_text(words, word);

        wchar_t *prev = current_word + word->len;

        current_word = wcstok(NULL, L", ", &ch);
        if (current_word == NULL)
            break;

        Sentence *sep = create_sentence();

        int sep_length = (current_word - prev);
        sep->len += sep_length;
        extend_sentence(sep);
        wmemcpy(sep->chars, sentence->chars + (prev - copy->chars), sep_length);

        push_text(seps, sep);
    }

    // processing

    Sentence *after_processing = create_sentence();
    for (int i = 0; i < words->len; i++)
    {
        Sentence *word = words->sentences[i];
        after_processing->len += word->len;
        extend_sentence(after_processing);
        swprintf(after_processing->chars + after_processing->len - word->len, word->len + 1, L"%ls", word->chars);

        if (seps->len <= i)
            continue;

        Sentence *sep = seps->sentences[i];
        after_processing->len += sep->len;
        extend_sentence(after_processing);
        swprintf(after_processing->chars + after_processing->len - sep->len, sep->len + 1, L"%ls", sep->chars);
    }
    print_sentence(after_processing);

    free_sentence(copy);
    free_sentence(after_processing);
    free_text(words);
    free_text(seps);
}

void work_with_words_and_seps_text(Text *text)
{
    for (int i = 0; i < text->len; i++)
    {
        work_with_words_and_seps_sentence(text->sentences[i]);
    }
}

int isPolindrom(Sentence *sentence)
{
    wchar_t *replacement = (wchar_t *)malloc(200 * sizeof(wchar_t));
    swprintf(replacement, 200, L"%ls", sentence->chars);
    towlower_string(&replacement);
    int start = 0;
    int end = wcslen(replacement)-1;
    while (start < end)
    {
        while (replacement[start] == ' ' || replacement[start] == ','|| replacement[start] == ';'|| replacement[start] == ':')
        {
            start++;
        }
        while (replacement[end] == ' ' || replacement[end] == ','|| replacement[end] == ';'|| replacement[end] == ':')
        {
            end--;
        }
        if (replacement[end] != replacement[start]){
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}
void polindrom(Text *text)
{
    for (int i = 0; i < text->len; i++)
    {
        Sentence *sentence = text->sentences[i];
        if (isPolindrom(sentence))
            print_sentence(sentence);
    }
}
