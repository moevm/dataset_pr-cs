#include "print_text.h"

void print_text(Text* text) {
    int len = text->count_sent;
    for(int i = 0; i<len; i++) {
        fputws((text->pr_sent)[i]->sentence, stdout);
        wprintf(L"\n");
    }
}
