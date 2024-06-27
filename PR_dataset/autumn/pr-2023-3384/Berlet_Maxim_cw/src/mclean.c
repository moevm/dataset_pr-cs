#include "mclean.h"
#include <stdlib.h>
void clean_memory(char** sentences, int counter){
    for(int i = 0; i < counter; i++){
        free(sentences[i]);
    }
    free(sentences);
}