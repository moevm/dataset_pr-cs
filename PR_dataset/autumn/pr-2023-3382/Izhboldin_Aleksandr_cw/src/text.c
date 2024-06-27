#include "text.h"

// Constructor for text
Text *Text_create(int *err)
{
    Text *new_text = (Text *)malloc(sizeof(Text));
    if (new_text == NULL)
    {
        Text_delete(&new_text);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }

    new_text->size = 0;
    new_text->memsize = TEXT_BUFFER;
    new_text->sentences = (Sentence **)calloc(TEXT_BUFFER, sizeof(Sentence *));
    if (new_text->sentences == NULL)
    {
        Text_delete(&new_text);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }

    return new_text;
}

// Destructor for text
void Text_delete(Text **text)
{
    for (size_t i = 0; i < (*text)->size; i++)
        if ((*text)->sentences[i] != NULL)
            Sentence_delete(&((*text)->sentences[i]));

    free((*text)->sentences);
    (*text)->sentences = NULL;
    free(*text);
    *text = NULL;
}

// Add sentence to text
void Text_add_sentence(Text *text, Sentence *sentence, int *err)
{
    if (text == NULL || sentence == NULL) return;

    if (*err)
    {
        Sentence_delete(&sentence);
        Text_delete(&text);
        return;
    }

    if (text->size >= text->memsize)
    {
        text->memsize += TEXT_BUFFER;
        text->sentences = (Sentence **)realloc(text->sentences, text->memsize * sizeof(Sentence *));
        if (text->sentences == NULL)
        {
            Sentence_delete(&sentence);
            Text_delete(&text);
            *err = MEMORY_ALLOC_ERROR;
            return;
        }
    }
    text->sentences[text->size] = sentence;

    text->size++;
}

// Recreate text and ignore NULL sentences
Text *Text_recreate(Text *text, int *err)
{
    if (text == NULL) return NULL;

    if (*err)
    {
        Text_delete(&text);
        return NULL;
    }

    Text *new_text = Text_create(err);
    if (*err)
    {
        Text_delete(&text);
        return NULL;
    }
    for (size_t i = 0; i < text->size; ++i)
    {
        if (text->sentences[i] != NULL)
        {
            Text_add_sentence(new_text, text->sentences[i], err);
            if (*err) return NULL;
        }
    }

    // delete old text object but leave sentences
    free(text->sentences);
    free(text);

    return new_text;
}