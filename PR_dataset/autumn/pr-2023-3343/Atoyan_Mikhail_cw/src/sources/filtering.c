#include "../include/filtering.h"

Text filter(Text text){
    int iterator = 0;
    int size = text.size;
    for (int i = 0; i < size; i++){
        if (text.sentences[i].amofwords <= 10){
            text.sentences[iterator] = text.sentences[i];
            iterator++;
            text.size++;
        }
        text.size--;
    }
    return text;
}