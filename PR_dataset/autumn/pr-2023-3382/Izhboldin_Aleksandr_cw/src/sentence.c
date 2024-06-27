#include "sentence.h"

// Constructor for sentences
Sentence *Sentence_create(int *err)
{
    Sentence *new_sentence = malloc(sizeof(Sentence));
    if (new_sentence == NULL)
    {
        Sentence_delete(&new_sentence);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }
    new_sentence->size = 0;
    new_sentence->memsize = SENTENCE_BUFFER;
    new_sentence->sentence = calloc(SENTENCE_BUFFER, sizeof(wchar_t));
    if (new_sentence->sentence == NULL)
    {
        Sentence_delete(&new_sentence);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }
    return new_sentence;
}

// Destructor for sentences
void Sentence_delete(Sentence **sentence)
{
    free((*sentence)->sentence);
    (*sentence)->sentence = NULL;
    free(*sentence);
    *sentence = NULL;
}

// Add symbol to sentence in the end
void Sentence_add_symbol(Sentence *sentence, wchar_t symbol, int *err)
{
    if (sentence == NULL) return;
    if (*err)
    {
        Sentence_delete(&sentence);
        return;
    }

    if (sentence->size >= sentence->memsize)
    {
        sentence->memsize += SENTENCE_BUFFER;
        sentence->sentence = realloc(sentence->sentence, sentence->memsize * sizeof(wchar_t));
        if (sentence->sentence == NULL)
        {
            Sentence_delete(&sentence);
            *err = MEMORY_ALLOC_ERROR;
            return;
        }
    }
    sentence->sentence[sentence->size] = symbol;
    sentence->size++;
}

// Adding a word to sentence
void Sentence_add_word(Sentence *sentence, wchar_t *word, int *err)
{
    if (sentence == NULL) return;

    if (*err)
    {
        Sentence_delete(&sentence);
        return;
    }

    for (size_t i = 0; i < wcslen(word); ++i)
    {
        Sentence_add_symbol(sentence, word[i], err);
        if (*err)
        {
            Sentence_delete(&sentence);
            return;
        }
    }
}

// Replace symbol in sentence
void Sentence_replace_symbol(Sentence *sentence, size_t index, wchar_t new_symbol, int *err)
{
    if (sentence == NULL) return;
    if (*err)
    {
        Sentence_delete(&sentence);
        return;
    }

    if (index < sentence->size)
        sentence->sentence[index] = new_symbol;
    else
    {
        *err = INDEX_ERROR;
        Sentence_delete(&sentence);
    }
}

// Return pointer to copy of sentence
Sentence *Sentence_copy(Sentence *sentence, int *err)
{
    if (sentence == NULL) return NULL;

    if (*err)
    {
        Sentence_delete(&sentence);
        return NULL;
    }

    Sentence *new_sentence = Sentence_create(err);
    if (*err)
    {
        Sentence_delete(&new_sentence);
        Sentence_delete(&sentence);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }

    if (sentence->memsize > new_sentence->memsize)
    {
        new_sentence->memsize = sentence->memsize;
        new_sentence->sentence = realloc(new_sentence->sentence, new_sentence->memsize * sizeof(wchar_t));
        if (new_sentence->sentence == NULL)
        {
            Sentence_delete(&new_sentence);
            Sentence_delete(&sentence);
            *err = MEMORY_ALLOC_ERROR;
            return NULL;
        }
    }
    new_sentence->size = sentence->size;
    new_sentence->sentence = wcscpy(new_sentence->sentence, sentence->sentence);

    return new_sentence;
}