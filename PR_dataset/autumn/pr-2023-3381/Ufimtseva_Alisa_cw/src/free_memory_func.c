#include "free_memory_func.h"
#include "structs.h"

void free_memory(struct Text text,int n){
    for (int i = 0; i < n; i++) {
        free(text.sentences[i]->sentence);
        free(text.sentences[i]->sentence_low);
        free(text.sentences[i]->last_word);
        free(text.sentences[i]);
    }
    free(text.sentences[n]->sentence);
    free(text.sentences[n]->sentence_low);
    free(text.sentences[n]);
    free(text.sentences);
}
