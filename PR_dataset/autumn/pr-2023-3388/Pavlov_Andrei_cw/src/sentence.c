#include "sentence.h"


Sentence* reallocate_sentence(Sentence* sentence) {
    size_t new_capacity = sentence->capacity + sentence->last_capacity;

    wchar_t* new_data = realloc(sentence->data, sizeof(wchar_t) * new_capacity);
    if (new_data == NULL) panic(L"Error: can`t allocate more memory for Sentence data!");
    
    sentence->data = wmemset(new_data + sentence->capacity, L'\0', sentence->last_capacity) - sentence->capacity;

    sentence->last_capacity = sentence->capacity;
    if (sentence->capacity == 0) sentence->last_capacity = 1;
    sentence->capacity = new_capacity;

    return sentence;
}

Sentence* init_sentence() {
    Sentence* sentence = malloc(sizeof(Sentence));
    if (sentence == NULL) panic(L"Error: can`t allocate memory for new Sentence instance!");

    sentence->data = NULL;
    sentence->capacity = 0;
    sentence->size = 0;
    sentence->last_capacity = 1;

    return sentence;
}

Sentence* free_sentence(Sentence* sentence) {
    free(sentence->data);
    sentence->data = NULL;
    sentence->capacity = 0;
    sentence->size = 0;
    sentence->last_capacity = 1;
    return sentence;
}

Sentence* append(Sentence* sentence, wchar_t symbol) {
    if (sentence->capacity <= sentence->size) reallocate_sentence(sentence);
    
    sentence->data[sentence->size] = symbol;
    sentence->size += 1;

    return sentence;
}

Sentence* read_sentence() {
    Sentence* sentence = init_sentence();
    wchar_t input; read(&input);

    if ((input == L'\n') && (*read(&input) == L'\n')) {
        free(sentence);
        return NULL;
    }
    if (input == WEOF) return NULL;
    //panic(L"Error: unexpected end of input stream! Check correctness of last sentence.");
    
    while (input != L'.') {
        if (sentence->size == 0 && ((input == L',') || (input == L' '))) {
            read(&input);
            continue;
        }

        if (input == L'\n') panic(L"Error: unexpected end of line! Check correctness of sentences.");
        if ((input == WEOF) || (input == L'\0')) break;

        append(sentence, input);
        read(&input);
    } append(sentence, input);
    
    return sentence;
}
