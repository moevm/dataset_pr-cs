#include "structs.h"
#include "Free.h"
void freeText(struct Text* txt) {
    if (txt->shouldFree){
        for (size_t i = 0; i < txt->n; i++) {
            free(txt->sents[i]->str);
        }
    }
}
