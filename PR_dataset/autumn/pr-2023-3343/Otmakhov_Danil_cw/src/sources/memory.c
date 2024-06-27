#include "../include/memory.h"

void freeText(Text text){
    for(size_t i = 0; i < text.size; i++)
        free(text.sentences[i].chars);
    free(text.sentences);
}

void checkMemoryAllocation(void *ptr){
   if (ptr == NULL) {
       puts("Error: memory allocation failed\n");
   }
}
