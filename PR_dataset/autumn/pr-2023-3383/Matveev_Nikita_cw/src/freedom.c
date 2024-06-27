#include "freedom.h"
void freedom(struct Text* text) {
    for (size_t i = 0; i < text->size; i++) {
        if (text->sentences[i] == NULL){
            free(text->sentences[i]);
            }
        else if(text->sentences[i] != NULL){
            free(text->sentences[i]);
        }
    }
    free(text->sentences);
}
