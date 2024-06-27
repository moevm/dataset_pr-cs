#include "../include/removedLower.h"
 
Text removeLowerCaseSentences(Text originalText) {
    Text text;
    text.sentences = malloc(sizeof(Sentence)*originalText.size);
    int count, check, textSize = 0;
    for (int i = 0; i < originalText.size; ++i) {
        count = 0;
        check = 0;
        wchar_t* str;
        str = wcsdup(originalText.sentences[i].words);
        wchar_t** words = splitSentence(originalText.sentences[i],&count);
 
        for (int j = 0; j < count; ++j) {
            if (iswupper(words[j][0])) {
                check = 1;
                break;
            }
        }
 
        if (check) {
            text.sentences[textSize].size = wcslen(str);
            text.sentences[textSize++].words = str;
        }
        free(words);
    }
 
    text.size = textSize;
    return text;
}