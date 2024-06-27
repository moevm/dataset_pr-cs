#include <wchar.h>
#include <wctype.h>
#include <locale.h>

struct Sentence {
    wchar_t* sentence;
    int len;
};

struct Text {
    struct Sentence** sentences;
    int len;
};