#include "../headers/print-uniqual-words.h"

void print_uniqual_words(struct Text text){
    wchar_t *buffer;
    struct Text text_from_words = {malloc(sizeof(struct Sentence*)), 0};
    wchar_t **list_of_words = malloc(sizeof(wchar_t*));
    int index = 0;
    for (size_t i =0; i<text.quantity_of_sentences;i++){
        for (size_t y=0;y<text.sentences[i].quantity_of_words;y++){
            list_of_words[index++] = text.sentences[i].words[y].word;
            list_of_words = realloc(list_of_words, sizeof(wchar_t*)*(index+1));
        }
    }
    for (size_t i =0;i< index;i++){
        int count_of_including = 0;
        for (size_t y =0; y<index;y++){
            if (i!=y && wcscmp(list_of_words[i], list_of_words[y]) == 0){
                count_of_including++;
                break;
            }
        }
        if (count_of_including == 0){
            text_from_words.sentences[text_from_words.quantity_of_sentences++].sentence = list_of_words[i];
            text_from_words.sentences = realloc(text_from_words.sentences, sizeof(struct Sentence)*(text_from_words.quantity_of_sentences+1));
        }
    }
    output(text_from_words);
    free_text(text);
}