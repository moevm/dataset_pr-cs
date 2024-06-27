#include "input.h"

void split_sentence(struct Sentence* sent){
    wchar_t* str = wcsdup(sent->sentence);
    str[wcslen(str)-1] = 0;
    int capacity = 1;
    sent->num_of_words = 0;
    wchar_t* ptr;
    
    sent->words = (wchar_t**)calloc(BLOCK, sizeof(wchar_t*));
    wchar_t* token = wcstok(str, L", \t", &ptr);

    while(token != NULL){
        
        if(sent->num_of_words + 1 > BLOCK*capacity){
            capacity++;
            sent->words = (wchar_t**)realloc(sent->words, sizeof(wchar_t*)*BLOCK*capacity);
        }
        sent->words[sent->num_of_words] = wcsdup(token);
        token = wcstok(NULL, L", \t", &ptr);
        sent->num_of_words++;
    }
}

wchar_t sent_input(struct Sentence* new_sentence){
    new_sentence->size = 0;
    wchar_t new_char = getwchar();
    int capacity = 1;
    int end_flag = 2;
    while((new_char == L' ' || new_char == L'\t' || new_char == L'\n') && !(end_flag == 1 && new_char == L'\n')){
        if(new_char == L'\n') end_flag--;
        new_char = getwchar();
    }

    if(new_char != L'\n') new_sentence->sentence = (wchar_t*)malloc(sizeof(wchar_t)*BLOCK); 

    while(new_char != L'.' && new_char != L'\n'){
        if(new_sentence->size + 3 > capacity*BLOCK){
            capacity++;
            new_sentence->sentence = (wchar_t*)realloc(new_sentence->sentence, sizeof(wchar_t)*BLOCK*capacity);
        }
        new_sentence->sentence[new_sentence->size] = new_char;

        new_char = getwchar();
        if(new_char == L'\n') error(2);
        new_sentence->size++;
    }
    if(new_char == L'.'){
        new_sentence->sentence[new_sentence->size] = L'.';
        new_sentence->size++;
        new_sentence->sentence[new_sentence->size] = L'\0';
        new_sentence->size++;

        split_sentence(new_sentence);
        }
    
    return new_char;
}

void text_input(struct Text* text){
    text->size = 0;
    wchar_t new_char = L'Z';
    int capacity = 1;

    text->text = (struct Sentence*)malloc(sizeof(struct Sentence)*BLOCK);

    while(new_char != L'\n'){
        if(text->size + 1 > capacity*BLOCK){
            capacity++;
            text->text = (struct Sentence*)realloc(text->text, sizeof(struct Sentence)*BLOCK*capacity);
        }
        new_char = sent_input(&text->text[text->size]);
        if (new_char != L'\n') {
                for(int i = 0; i < text->size; i++) {
                if(!wcscasecmp(text->text[i].sentence, text->text[text->size].sentence)){
                    text->size--;
                    break;
                }
            }
        }
        
        text->size++;
    }
    text->size--;
}
