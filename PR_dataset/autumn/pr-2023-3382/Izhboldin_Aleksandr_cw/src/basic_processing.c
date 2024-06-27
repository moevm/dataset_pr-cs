#include "basic_processing.h"

// Function 0
void print_basic_processed_text(int *err)
{
    if (*err) return;
    Text *text = Text_read(err);
    if (*err) return;
    text = basic_processing(text, err);
    if (*err) return;
    Text_print(text);
    Text_delete(&text);
}

Text *basic_processing(Text *text, int *err)
{
    if (text == NULL) return NULL;

    for (size_t i = 0; i < text->size; ++i)
        if (text->sentences[i] != NULL)
            for (size_t j = i + 1; j < text->size; ++j)
                if (text->sentences[j] != NULL)
                    if (!wcscasecmp(text->sentences[i]->sentence, text->sentences[j]->sentence))
                        Sentence_delete(&text->sentences[j]);

    text = Text_recreate(text, err);
    if (*err) return NULL;

    return text;
}
