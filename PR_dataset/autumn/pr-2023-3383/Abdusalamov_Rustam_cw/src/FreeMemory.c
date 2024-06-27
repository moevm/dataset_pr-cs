#include "FreeMemory.h"

void FreeMemory(char** text, int sentences_count) {
    for (int i = 0; i < sentences_count; i++) {
        free(text[i]);
    }
    free(text);
}
