#include "defence.h"

void Sentence_tolower(Sentence *sentence)
{
    for (size_t i = 0; i < sentence->size; ++i)
        sentence->sentence[i] = towlower(sentence->sentence[i]);
}

bool check_word(Sentence *base, Sentence *word, int *err)
{
    Sentence *sencopy1 = Sentence_copy(base, err);
    Sentence_tolower(sencopy1);
    Sentence *sencopy2 = Sentence_copy(word, err);
    Sentence_tolower(sencopy2);
    for (size_t i = 0; i < sencopy2->size; ++i) {
//        wprintf(L"%ls %lc\n", sencopy1->sentence, sencopy2->sentence[i]);
        if (wcschr(sencopy1->sentence, sencopy2->sentence[i]) == NULL) {
            Sentence_delete(&sencopy1);
            Sentence_delete(&sencopy2);
            return false;
        }
    }
    Sentence_delete(&sencopy1);
    Sentence_delete(&sencopy2);
    return true;
}

void def_task(int *err)
{
    Sentence *word = Sentence_create(err);
    wchar_t symbol;
    while (true)
    {
        symbol = getwchar();
        if (symbol == L'\n')
            break;
        Sentence_add_symbol(word, symbol, err);
    }
    Sentence_add_symbol(word, L'\0', err);
    Text *text = Text_read(err);
//    Sentence *sentence = text->sentences[0];
//    wprintf(L"%d\n", check_word(word, sentence, err));

    text = basic_processing(text, err);
    Text *new_text = Text_create(err);

    for (size_t i = 0; i < text->size; ++i)
    {
        Sentence *sencopy = Sentence_copy(text->sentences[i], err);

        wchar_t *buffer;
        wchar_t *split = wcstok(sencopy->sentence, L" ,.\n\t", &buffer);

        Sentence *processed = Sentence_create(err);

        while (split != NULL)
        {
//            wprintf(L"%ls\n", split);
            Sentence *new_word = Sentence_create(err);
            Sentence_add_word(new_word, split, err);
            if (check_word(word, new_word, err))
            {
                Sentence_add_word(processed, split, err);
                Sentence_add_symbol(processed, L'\n', err);
            }
            split = wcstok(NULL, L" ,.\n\t", &buffer);
            Sentence_delete(&new_word);
        }

        if (processed->size > 0){
            Sentence_replace_symbol(processed, processed->size - 1, L'\0', err);
            Text_add_sentence(new_text, processed, err);
        } else
            Sentence_delete(&processed);

        Sentence_delete(&sencopy);
    }
    Text_print(new_text);

    Text_delete(&new_text);
    Text_delete(&text);
    Sentence_delete(&word);
}