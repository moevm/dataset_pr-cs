#ifndef CW_TEXT_PROCESSING_H
#define CW_TEXT_PROCESSING_H

#include "wchar.h"
#include "text.h"

Text *edit_verbs(Text *text);

Text *find_word(Text *text, wchar_t *word);

Text *delete_long_sentences(Text *text, size_t max_words_count);

Sentence *find_words_consisting_of_chars(Text *text, wchar_t *chars);

#endif //CW_TEXT_PROCESSING_H
