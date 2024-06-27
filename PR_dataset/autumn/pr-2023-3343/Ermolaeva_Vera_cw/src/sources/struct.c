#include <wchar.h>

typedef struct {
    wchar_t* sentence;
    int size;
} Sentence;

typedef struct {
    Sentence* sentences;
    int size;
    int real_size;
} Text;