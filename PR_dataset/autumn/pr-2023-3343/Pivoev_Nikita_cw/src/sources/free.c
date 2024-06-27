#include "../include/free.h"

void freeText(Text text) {
    for (int i = 0; i < text.size; ++i)
        free(text.sentences[i].words);
}