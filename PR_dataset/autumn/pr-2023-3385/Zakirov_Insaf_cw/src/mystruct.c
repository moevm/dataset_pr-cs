#include "mystruct.h"
#include "myinout.h"
#include "mysupport.h"

void inittext(Text* text) {
    text->count = 0;
    text->sentence = (Sentence*) malloc((text->count + 1) * sizeof(Sentence));
    
    if (text->sentence == NULL) {
        printallocerror("inittext", "sentence", "malloc");
        myfreetext(text);
        exit(1);
    }
    
    text->sentence[0].count = 0;
    text->sentence[0].symbol = (wchar_t*) malloc((text->sentence[0].count + 1) * sizeof(wchar_t));

    if (text->sentence[0].symbol == NULL) {
        printallocerror("inittext", "symbol", "malloc");
        myfreetext(text);
        exit(1);
    }
}