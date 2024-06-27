#pragma once

struct Sentence{
    wchar_t* sentence;
    wchar_t** list_of_words;
    int len_of_sentence;
    int count_of_words;
};

struct Text{
    int count_of_sentences;
    struct Sentence* list_of_sentences;
};