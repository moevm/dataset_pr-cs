#include "output_text.h"

void output_text(struct Text* text){
    for(int i = 0; i < text->size; i++) {
        wprintf(L"%ls\n", text->text[i].sentence);
    }
}