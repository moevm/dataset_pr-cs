#include "printByPattern.h"

void printByPattern(Text text, wchar_t *pattern){
    for (int i = 0; i < text.size; i++){
        int matchedWordCounter = 0;
        wchar_t *tokenBuffer;
        wchar_t *word = wcstok(wcsdup(text.sentences[i].chars), L" .,", &tokenBuffer);

        while (word != NULL){
            if (isMatch(pattern, word)){
                matchedWordCounter++;
            }
            else{
                break;
            }

            word = wcstok(NULL, L" .,", &tokenBuffer);
        }

        if (matchedWordCounter == text.sentences[i].wordCounter){
            wprintf(L"%ls\n", text.sentences[i].chars);
        }
        
    }
}

int isMatch(wchar_t *pattern, wchar_t *word){
    int patternLength = wcslen(pattern);
    int wordLength = wcslen(word);
    int patternIndex = 0;
    int wordIndex = 0;
    int patternWildcardIndex = -1;
    int wordWildcardIndex = -1;

    while (wordIndex < wordLength) {
        if (pattern[patternIndex] == L'?') {
            patternIndex++;
            wordIndex++;
        } else if (pattern[patternIndex] == L'*') {
            patternWildcardIndex = patternIndex;
            wordWildcardIndex = wordIndex;
            patternIndex++;
        } else if (patternIndex < patternLength && pattern[patternIndex] == word[wordIndex]) {
            patternIndex++;
            wordIndex++;
        } else if (patternWildcardIndex != -1) {
            patternIndex = patternWildcardIndex + 1;
            wordIndex = wordWildcardIndex + 1;
            wordWildcardIndex++;
        } else {
            return 0;
        }
    }

    while (patternIndex < patternLength && pattern[patternIndex] == L'*') {
        patternIndex++;
    }

    return patternIndex == patternLength;

}