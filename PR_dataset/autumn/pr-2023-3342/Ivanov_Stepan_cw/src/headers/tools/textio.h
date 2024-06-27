#pragma once

#ifndef _TEXTIO_H
#define _TEXTIO_H

#include "word.h"
#include "sentence.h"
#include "text.h"

Wsize_t print_word(Word_t *);
size_t scan_word(Word_t *);

Ssize_t print_sentence(Sentence_t *);
wchar_t scan_sentence(Sentence_t *);

Tsize_t print_text(Text_t *);
size_t scan_text(Text_t *);

Word_t *getword();
Sentence_t *getsentence();
Text_t *gettext();

static inline int
print_message(const wchar_t *message)
{
    return wprintf(L"%ls\n", message);
}

#endif // _TEXTIO_H
