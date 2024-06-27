#include <stdio.h>
#include <wchar.h>
#include <wctype.h>


#include "structures.h"
#include "avg_len.h"





int cmp(const void* a, const void* b) {
    const struct Sentence** sent1 = (const struct Sentence**)a;
    const struct Sentence** sent2 = (const struct Sentence**)b;
    double avg_len1 = avg_word_len((*sent1)->s);
    double avg_len2 = avg_word_len((*sent2)->s);

    if ((double)(avg_len1) > (double)(avg_len2))
        return 1;
    else if ((double)(avg_len1) < (double)(avg_len2))
        return -1;
    else
        return 0;
    
}


int cmpw(const void* a, const void* b) {
    const wchar_t** word1 = (const wchar_t**)a;
    const wchar_t** word2 = (const wchar_t**)b;
    if (wcslen(*word1) > wcslen(*word2))
        return -1;
    else if (wcslen(*word1) < wcslen(*word2))
        return 1;
    else
        return 0;
}