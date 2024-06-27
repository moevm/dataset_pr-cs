#include "../include/newTask.h"
#define SIZE_STEP 20

Text newTask(Text originalText) {
    Text text;
    text.sentences = malloc(sizeof(Sentence)+1);
    text.size = 0;
    int wordCount = 0;
    int currentSize = 0;
    int maxSize = 1;
    wchar_t** words = splitSentence(originalText.sentences[0],&wordCount);
    words[wordCount-1][wcslen(words[wordCount-1])-1] = '\0';

    for (int i = 1; i < originalText.size; ++i) {
        wchar_t* str;
        str = wcsdup(originalText.sentences[i].words);
        int newWordCount = 0;
        int correctSentence = 1;
        wchar_t** newWords = splitSentence(originalText.sentences[i],&newWordCount);
        newWords[newWordCount-1][wcslen(newWords[newWordCount-1])-1] = '\0';
        

        for (int j = 0; j < newWordCount; ++j) {
            int breakFlag = 1;
            for (int k = 0; k < wordCount; ++k) {
                if (wcscasecmp(newWords[j],words[k]) == 0) {
                    breakFlag = 0;
                    break;
                }
            }

            if (breakFlag)
                correctSentence = 0;
        }
        if (correctSentence) {

            text.sentences[currentSize].words = str;
            text.sentences[currentSize++].size = wcslen(str);
            text.size = currentSize;
            if (currentSize >= maxSize-2) {
                maxSize += SIZE_STEP;
                text.sentences = realloc(text.sentences, sizeof(Sentence)*maxSize);
            }
        }
        free(newWords);
    }
    return text;
}