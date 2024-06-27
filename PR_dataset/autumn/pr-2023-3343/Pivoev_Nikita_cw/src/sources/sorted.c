#include "../include/sorted.h"
 
int compareVowels(const void* a, const void* b) {
    const wchar_t* first = *((wchar_t**)a);
    const wchar_t* second = *((wchar_t**)b);
    int charCountA = 0;
    int charCountB = 0;
 
    for (int i = 0; i < wcslen(first); ++i) {
            if (wcschr(L"aeiouyAEIOUYаеёиоуэюяАЕЁИОУЭЮЯ",first[i]))
                ++charCountA;
    }
 
    for (int i = 0; i < wcslen(second); ++i) {
            if (wcschr(L"aeiouyAEIOUYаеёиоуэюяАЕЁИОУЭЮЯ",second[i]))
                ++charCountB;
    }
 
    if (charCountA > charCountB)
        return 1;
    else if (charCountA < charCountB)
        return -1;
 
    if (wcslen(first) > wcslen(second))
        return 1;
    else if (wcslen(first) < wcslen(second))
        return -1;
 
    if (wcscmp(first,second) > 0)
        return 1;
    else if (wcscmp(first,second) < 0)
        return -1;
    return 0;
}
 
void sortWords(Text text) {
    for (int q = 0; q < text.size; ++q) {
        int wordCount = 0;
        wchar_t* splitters = calloc(text.sentences[q].size+1, sizeof(wchar_t));
        int splittersSize = 0;
        splitters[splittersSize++] = L'*';
 
        for (int i = 0; i < text.sentences[q].size; ++i) {
            if (text.sentences[q].words[i] == L' ' || text.sentences[q].words[i] == L',' || text.sentences[q].words[i] == L'\t' || text.sentences[q].words[i] == L'.') {
                splitters[splittersSize++] = text.sentences[q].words[i];
            }
            else if (splitters[splittersSize-1] != L'*') {
                splitters[splittersSize++] = L'*';
            }
        }
        splitters[splittersSize++] = L'\0';
        wchar_t** words = splitSentence(text.sentences[q],&wordCount);
        --wordCount;
        words[wordCount][wcslen(words[wordCount])-1] = 0;
 
        qsort(words,wordCount,sizeof(wchar_t*),compareVowels);
 
        int current = 0;
        for (int i = 0; i < splittersSize; ++i) {
            if (splitters[i] == L'*')
                wprintf(L"%ls",words[current++]);
            else
                wprintf(L"%c", splitters[i]);
        }
        wprintf(L"\n");
 
        free(splitters);
        free(words);
    }
    freeText(text);
}