#ifndef CW_TEXT_H
#define CW_TEXT_H

#include "sentence.h"

struct Text;
typedef struct Text Text;

Text *Text_create();

void Text_destroy(Text *Text);

Sentence **Text_get_sentences(Text *text);

size_t Text_get_length(Text *text);

Sentence *Text_get_sentence(Text *text, size_t index);

Text *Text_extend(Text *Text, size_t extension_size);

Text *Text_append_sentence(Text *text, Sentence *sentence);

Text *Text_delete_sentence(Text *text, size_t index);

Text *Text_optimize_size(Text *text);

Text *Text_delete_duplicates(Text *text);

#endif //CW_TEXT_H
