#include "RemoveNumText.h"

int SpacesCheck(const wchar_t* str, int startIndex, int endIndex) {
    return iswspace(str[startIndex - 1]) && iswspace(str[endIndex + 1]);
}

void RemoveNumSentence(struct Sentence* S) {
    wchar_t* str = S->str;
    int sentenceLength = S->l;

    wchar_t* filteredStr = (wchar_t*) malloc((sentenceLength + 1) * sizeof(wchar_t));
    int filteredLength = 0;

    int i = 0;
    while (i < sentenceLength) {
        if (iswdigit(str[i])) {
            int startIndex = i;
            int endIndex = i;

            while (iswdigit(str[i]) && i < sentenceLength) {
                endIndex = i;
                i++;
            }

            if (!SpacesCheck(str, startIndex, endIndex)) {
                while (startIndex <= endIndex) {
                    filteredStr[filteredLength] = str[startIndex];
                    filteredLength++;
                    startIndex++;
                }
            }
        } else {
            filteredStr[filteredLength] = str[i];
            filteredLength++;
            i++;
        }
    }

    filteredStr[filteredLength] = L'\0';

    free(str);
    S->str = filteredStr;
    S->l = filteredLength;
}

void RemoveNumText(struct Text* text) {
    struct Sentence** txt = text->txt;
    int textLength = text->l;

    for (int i = 0; i < textLength; i++) {
        struct Sentence* sentence = txt[i];
        RemoveNumSentence(sentence);
    }
}
