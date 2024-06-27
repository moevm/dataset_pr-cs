#include "sentence.h"


Sentence* realloc_sentence(Sentence* sentence) {
    size_t new_capacity = sentence->capacity + ALLOC_SENT;

    wchar_t* new_data = realloc(sentence->data, sizeof(wchar_t) * new_capacity);
    if (new_data == NULL) {
        error(L"Error: нет памяти для нового предложения!");
    }
    
    sentence->data = wmemset(new_data + sentence->capacity, 0x00, ALLOC_SENT) - sentence->capacity;
    sentence->capacity = new_capacity;

    return sentence;
}

Sentence* sentence_initialization() {
    Sentence* sentence = malloc(sizeof(Sentence));
    if (sentence == NULL) {
        error(L"Error: нет памяти для нового предложения!");
    }

    sentence->data = NULL;
    sentence->capacity = 0;
    sentence->size = 0;

    return sentence;
}

Sentence* sentence_free(Sentence* sentence) {
    free(sentence->data);
    sentence->data = NULL;
    sentence->capacity = 0;
    sentence->size = 0;
    return sentence;
}

Sentence* add_symbol(Sentence* sentence, wchar_t symbol) {
    if (sentence->capacity <= sentence->size) realloc_sentence(sentence);
    
    sentence->data[sentence->size] = symbol;
    sentence->size += 1;

    return sentence;
}

Sentence* read_sentence() {
    Sentence* sentence = sentence_initialization();
    wchar_t input; read(&input);

    if (input == L'\n') {
        read(&input);
        if (input == L'\n') {
            return NULL;
        }
    }

    if (input == WEOF) {
        error(L"Error: неожиданный конец ввода! Проверьте правильность последнего предложения.");
    }
    
    while (input != L'.') {
        if (sentence->size == 0 && ((input == L',') || (input == L' '))) {
            read(&input);
            continue;
        }

        if (input == L'\n') {
            error(L"Error: неожиданный перенос строки! Проверьте правильность предложений.");
        }

        if (input == WEOF) {
            error(L"Error: неожиданный конец ввода! Проверьте правильность последнего предложения.");
        }

        add_symbol(sentence, input);
        read(&input);
    } 
    
    add_symbol(sentence, input);

    return sentence;
}

Sentence* double_word(Sentence* sentence){
    int counter = 0;
    int i = 0;
    int repeat = 0;
    while (i < sentence->size-1) {
        if (sentence->data[i] != ' '){
            write(sentence->data[i]);
            i++;
            counter += 1;
        }
        else{
            if (repeat == 1) {
                write(L' ');
                repeat = 0;
                i++;
                counter = 0;
            }
            else{
                i -= counter;
                repeat = 1;
                write(L' '); 
            }

        }

        if (i == sentence->size-1) {
            if (repeat == 1) {
                write(L'.');
                break;
            }
            else{
                i -= counter;
                repeat = 1;
                write(L' '); 
            }
        }
    }
    write(L'\n');
}