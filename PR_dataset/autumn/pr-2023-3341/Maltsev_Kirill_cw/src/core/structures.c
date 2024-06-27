#include <stdlib.h>

#include "structures.h"

Sentence* createSentence() {
    Sentence* s = (Sentence*) malloc(sizeof(Sentence));
    s->line = NULL;
    s->sentenceSize = 0;
    return s;
}

Text* createText() {
    Text* text = (Text*) malloc(sizeof(Text));
    text->sentences = NULL;
    text->sentencesNumber = 0;
    return text;
}