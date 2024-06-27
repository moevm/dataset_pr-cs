#include <wchar.h>
#include "structures.h"
#include "len_third.h"

int cmp(const void *a, const void *b) {
    struct Sentence *sentence_a = *(struct Sentence **)a;
    struct Sentence *sentence_b = *(struct Sentence **)b;
    int len_a = len_third(sentence_a->str);
    int len_b = len_third(sentence_b->str);
    if (len_a < len_b) {
        return -1;
    } else if (len_a > len_b) {
        return 1;
    } else {
        return 0;
    }
}