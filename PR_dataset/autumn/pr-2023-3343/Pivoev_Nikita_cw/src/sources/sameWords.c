#include "../include/sameWords.h"

void printSameWords(Text text) {
    int wordCount;
    for (int i = 0; i < text.size; ++i) {
        wordCount = 0;
        wchar_t* str = calloc(wcslen(text.sentences[i].words),sizeof(wchar_t));
        str = wcsdup(text.sentences[i].words);
        wchar_t** words = splitSentence(text.sentences[i],&wordCount);
        int* count = malloc(sizeof(int)*wordCount);
        words[wordCount-1][wcslen(words[wordCount-1])-1] = '\0';

        for (int j = 0; j < wordCount; ++j) {
            count[j] = 1;
            for (int k = 0; k < j; k++) { 
                if (wcscmp(words[j], words[k]) == 0) {
                    ++count[k];
                    count[j] = 0; 
                    break;
                }
            }
        }

        wprintf(L"%ls\nКоличество одинаковых слов: ", str);
        int uniqueCount = 0;
        for (int j = 0; j < wordCount; j++) {
            if (count[j] > 1) 
                uniqueCount += count[j];
        }

        wprintf(L"%d.\n",uniqueCount);

        free(words);
        free(str);
        free(count);
    }
    freeText(text);
}