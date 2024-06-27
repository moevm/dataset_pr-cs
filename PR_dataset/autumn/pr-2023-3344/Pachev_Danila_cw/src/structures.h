#ifndef structures_h
#define structures_h
#include <wchar.h>
struct Sentence{
    wchar_t *sentence;
    size_t len;
    size_t diff_index;
};

struct Text{
    struct Sentence **text;
    size_t len;
    size_t count_all_words;
};
#endif /* Header_h */
