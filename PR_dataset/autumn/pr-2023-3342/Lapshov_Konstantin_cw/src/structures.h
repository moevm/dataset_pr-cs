#pragma once
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

struct Word {
    wchar_t *letters;
    wchar_t *punctuation;
    size_t quantity_of_letters;
    size_t quantity_of_punctuation;
};

struct Sentence{
    struct Word *words;
    size_t quantity_of_words;
};

struct Text{
    struct Sentence *sentences;
    size_t quantity_of_sentences;
};

struct Unique_Word{
    wchar_t *letters;
    size_t word_count;
};

struct Word create_word();
void add_letters(struct Word* word, wchar_t symbol);
void add_punctuation(struct Word* word, wchar_t symbol);

struct Sentence create_sentence();
void add_word(struct Sentence* sen, struct Word word);

struct Text create_text();
void add_sentence(struct Text *text, struct Sentence sen);

struct Unique_Word create_unique_word(wchar_t* word);
size_t quantity_of_latin(struct Sentence sen);