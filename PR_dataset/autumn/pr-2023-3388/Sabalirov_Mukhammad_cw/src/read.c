#include "read.h"
#include "strings.h"

bool wide_str_case_compare(const wchar_t *first, const wchar_t *second) {
    while (*first && *second) {
        if (towupper(*first) != towupper(*second))
            return false;
        first++;
        second++;
    }

    return (*first == END_STR && *second == END_STR);
}

bool is_duplicate(struct Text *text, struct Sentence *sentence){
    for (size_t i = 0; i < text->len; i++)
        if (wide_str_case_compare(text->data[i]->data, sentence->data))
            return true;
    return false;
}

wchar_t* read(){
    wchar_t input = getwchar();
    wchar_t last_char;
    wchar_t *text = NULL;
    size_t len = 0;
    while (input != L'\n' || last_char != L'\n'){
        if (input == WEOF)
            panic(INPUT_ERROR);
        text = realloc(text, (len+1) * sizeof(wchar_t));
        if (text == NULL)
            panic(MEM_ERROR);
        text[len++] = input;
        last_char = input;
        input = getwchar();
    }
    text = realloc(text, (len+1) * sizeof(wchar_t));
    if(text[len-2]==L'.')
        text[len-2] = END_STR;
    else
        text[len-1] = END_STR;
    return text;
}

struct Sentence* read_sentence(wchar_t *text, size_t start){
    struct Sentence *sentence = malloc(sizeof(struct Sentence));
    if (sentence == NULL) 
        panic(MEM_ERROR);
    
    sentence->len = 0;
    sentence->data = NULL;
    size_t i = start;
    bool have_non_space = false;
    while (text[i] != L'.' && text[i] != END_STR){
        if (iswspace(text[i]) && !have_non_space){
            i++;
            continue;
        }
        sentence->data = realloc(sentence->data, (sentence->len+1) * sizeof(wchar_t));
        if (sentence->data == NULL)
            panic(MEM_ERROR);
        sentence->data[sentence->len++] = text[i];
        have_non_space = true;
        i++;
    }   

    if (text[i] == END_STR)
        sentence->last_index = -1;
    else
        sentence->last_index = i+1;

    sentence->data = realloc(sentence->data, (sentence->len+2) * sizeof(wchar_t));
    if (sentence->data == NULL)
            panic(MEM_ERROR);
    sentence->data[sentence->len++] = L'.';
    sentence->data[sentence->len++] = END_STR;
    return sentence;
}

struct Text* read_text(){
    struct Text *text = malloc(sizeof(struct Text));
    if (text == NULL)
        panic(MEM_ERROR);

    text->len = 0;
    text->data = NULL;

    struct Sentence *sentence = malloc(sizeof(struct Sentence*));
    if (sentence == NULL) 
        panic(MEM_ERROR);
    
    sentence->last_index = 0;

    wchar_t *input = read();
    
    do {
        sentence = read_sentence(input, sentence->last_index);
        if (sentence == NULL)
            panic(MEM_ERROR);
        if (!is_duplicate(text, sentence)){
            text->data = realloc(text->data, (text->len+1)*sizeof(struct Sentence*));
            if (text->data == NULL)
                panic(MEM_ERROR);
            
            text->data[text->len++] = sentence;
        }
    } while (sentence->last_index != -1);

    return text;
}