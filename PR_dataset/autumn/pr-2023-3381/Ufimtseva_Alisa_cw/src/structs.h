#ifndef STRUCTS
#define STRUCTS
#include <wchar.h>

struct Sentence { 
    wchar_t* sentence;//предложение
    wchar_t* sentence_low;//предложение без табуляции
    int amount_of_letters; //длина предложения (индекс последнего)
    int amount_of_words;//количество слов
    wchar_t* last_word;//последнее слово
    int len_last_word;//длина последнего слова
};

struct Text { 
    struct Sentence** sentences;//массив предложений
    int amount_of_sentences; //количество предложений
};
#endif