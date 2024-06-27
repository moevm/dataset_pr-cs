//
// Created by rect on 18.11.2023.
//

#include "../include/upperCaseWords.h"

Text getUpperCaseWords(Text text) {
    Text newText;
    int wordArrayBuffer = 1;
    int wordArraySize = 0, newTextSize = 0;
    Word *wordArray = malloc(wordArrayBuffer * sizeof(Word));
    for (int i = 0; i < text.size; i++) {
        Sentence tempSentence = text.sentences[i];
        wchar_t *tokBuffer;
        wchar_t *word = wcstok(tempSentence.chars, L" .,", &tokBuffer);

        while (word != NULL) {

            if (iswupper(word[0]) && iswupper(word[wcslen(word) - 1])) {
                int founded = 0;
                for (int j = 0; j < wordArraySize; ++j) {
                    if (wcscmp(word, wordArray[j].chars) == 0) {
                        founded = 1;
                        if ((wordArray[j].occurrences[wordArray[j].occurrencesSize - 1]) == i + 1) continue;
                        wordArray[j].occurrences = realloc(wordArray[j].occurrences,sizeof(int) * (wordArray[j].occurrencesSize * 2));
                        wordArray[j].occurrences[wordArray[j].occurrencesSize++] = i + 1;
                    }
                }
                if (founded == 0) {
                    wordArray[wordArraySize].occurrences = malloc(sizeof(int) * 1);
                    wordArray[wordArraySize].occurrencesSize = 0;
                    wordArray[wordArraySize].occurrences[wordArray[wordArraySize].occurrencesSize++] = i + 1;
                    wordArray[wordArraySize].chars = wcsdup(word);
                    wordArraySize++;
                    if (wordArrayBuffer <= wordArraySize) {
                        wordArrayBuffer += 1;
                        wordArray = realloc(wordArray, wordArrayBuffer * sizeof(Word));
                    }
                }
            }

            word = wcstok(NULL, L" .,", &tokBuffer);
        }
        free(word);
        free(tokBuffer);
        free(text.sentences[i].chars);
    }

    newText.sentences = malloc(sizeof(Sentence) * wordArraySize - 1);
    for (int i = 0; i < wordArraySize; ++i) {
        int wordStructToStringBuffer = (wcslen(wordArray[i].chars) + 3) * sizeof(wchar_t);
        wchar_t *wordStructToString = calloc((wcslen(wordArray[i].chars) + 3), sizeof(wchar_t));
        wchar_t charOccurrences[wordArray[i].occurrencesSize][100];
        wcscat(wordStructToString, wordArray[i].chars);
        wcscat(wordStructToString, L": ");

        for (int j = 0; j < wordArray[i].occurrencesSize; ++j) {
            swprintf(charOccurrences[j], 100, L"%d", wordArray[i].occurrences[j]);
            int num = wordArray[i].occurrences[j];
            int count = 0;
            while (num != 0) {
                num /= 10;
                count++;
            }
            wordStructToStringBuffer+= ((count + 1) * sizeof(wchar_t));
            wordStructToString = realloc(wordStructToString,wordStructToStringBuffer);
            wcscat(wordStructToString, charOccurrences[j]);
            wcscat(wordStructToString, L" ");
        }

        free(wordArray[i].occurrences);
        free(wordArray[i].chars);
        newText.sentences[newTextSize].chars = wcsdup(wordStructToString);
        free(wordStructToString);
        newText.sentences[newTextSize].size = wcslen(newText.sentences[newTextSize].chars);
        newTextSize++;
    }
    newText.size = newTextSize;
    return newText;
}