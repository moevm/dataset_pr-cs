#include "../include/masks.h"
 
int compare(const void* a, const void* b) {
    const wchar_t* first = *((wchar_t**)a);
    const wchar_t* second = *((wchar_t**)b);
 
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
 
void findMask(Text text) {
    for (int l = 0; l < text.size; ++l) {
        Sentence sentence = text.sentences[l];
        wchar_t* printText = calloc(text.sentences[l].size,sizeof(wchar_t)); 
        printText = wcsdup(sentence.words);
        int wordCount = 0;
        int charCount = 0;
        wchar_t** words = splitSentence(sentence,&wordCount);
        words[wordCount-1][wcslen(words[wordCount-1])-1] = '\0';
        qsort(words,wordCount,sizeof(wchar_t*),compare);
 
        for (int i = 0; i < wordCount; ++i)
            charCount += wcslen(words[i]);
 
        wchar_t* mask = calloc(charCount*3,sizeof(wchar_t));
        wchar_t stateChar;
        int inAllWords;
        int inCurrentWord;
        int prevIndex;
        int maskLen = 0;
        int end = 0;
        int once;
        int onceCheck = 1;
        int* indexArray = calloc(wordCount, sizeof(int));
        int* prevIndexArray = calloc(wordCount, sizeof(int));
 
        for (int j = 0; j < wcslen(words[0]); ++j) {
            stateChar = words[0][j];
            inAllWords = 1;
            int singleStep = 0;
            int manySteps = 0;
            for (int k = 1; k < wordCount; ++k) {
                inCurrentWord = 0;
                once = 1;
                for (int q = indexArray[k]; q < wcslen(words[k]); ++q) {
                    if (indexArray[k] != 0 && once) {
                        ++q;
                        once = 0;
                    }

                    if (stateChar == words[k][q]) {
                        if (j == 0 && q != 0) {
                            wcscat(mask,L"?");
                            ++maskLen;
                        }
 
                        if (j != 0) {
                            int diff = q - indexArray[k];
                            if (diff == 1)
                                singleStep = 1;
                            if (diff >= 2)
                                manySteps = 1;
                            if (indexArray[k] != 0)
                                prevIndexArray[k] = indexArray[k];
                        }
 
                        indexArray[k] = q;
                        inCurrentWord = 1;
                        if (j == wcslen(words[0])-1 && q != wcslen(words[k])-1) {
                            end = 1;
                        }
                        break;
                    }
                }
                if (!inCurrentWord)
                    inAllWords = 0;
            }
 
            if (inAllWords) {
                if (j != 0) {
                    if (j - prevIndex == 1)
                        singleStep = 1;
                    if (j - prevIndex >= 2)
                        manySteps = 1;
                    if (singleStep && manySteps) {
                        wcscat(mask,L"?");
                        ++maskLen;
                        for (int k = 1; k < wordCount; ++k) {
                            if (onceCheck)
                                continue;
                            indexArray[k] = prevIndexArray[k];
                        }
                        onceCheck = 0;
                        continue;
                    }
                }
                prevIndex = j;
                mask[maskLen] = stateChar;
                ++maskLen;
            }
            else {
                for (int k = 1; k < wordCount; ++k) {
                    indexArray[k] = prevIndexArray[k];
                }                
                wcscat(mask,L"?");
                ++maskLen;
            }
        }
        
        if (end) {
            wcscat(mask,L"?");
            ++maskLen;
        }
 
        if (mask[0] == L'?')
            mask[0] = L'*';
 
        if (mask[maskLen-1] == L'?')
            mask[maskLen-1] = L'*';
        mask[maskLen] = '\0';
 
        wchar_t* newMask = malloc(sizeof(wchar_t)*(maskLen+1));
        int newLen = 0;
        int questionCheck = 1;
        for (int i = 0; i < maskLen; ++i) {
            if (mask[i] != L'?') {
                newMask[newLen++] = mask[i];
                questionCheck = 1;
            }
            else if (mask[i] == L'?' && questionCheck) {
                newMask[newLen++] = mask[i];
                questionCheck = 0;
            }
        }
        if (mask[maskLen-1] == L'*')
            newMask[newLen-1] = L'*';
 
        if (newLen >= 2 && newMask[newLen-2] == L'?' && newMask[newLen-1] == L'*') {
            --newLen;
            newMask[newLen-1] = L'*';
        }
 
        if (newLen == 2 && newMask[0] == L'*' && newMask[1] == L'*') {
            --newLen;
        }
        newMask[newLen] = L'\0';
 
        if (newLen >= 2 && newMask[0] == L'*' && newMask[1] == L'?') {
            wchar_t* veryNewMask = calloc(newLen+1,sizeof(wchar_t));
            int cnt = 0;
            for (int r = 0; r < newLen; ++r) {
                if (r != 1)
                    veryNewMask[cnt++] = newMask[r];
            }
            veryNewMask[newLen] = L'\0';
            wprintf(L"%ls\n", veryNewMask);
        }
        else 
            wprintf(L"%ls\n", newMask);
        wprintf(L"%ls\n", printText);
 
        free(mask);
        free(newMask);
        free(indexArray);
        free(prevIndexArray);
    }
    freeText(text);
}