#include "Function2.h"
#include "Common.h"
void Function2(char** text, int sentences_count) {
    for (int i = 0; i < sentences_count; ++i) {
        char* sentence = text[i];
        int len = strlen(sentence);
        for (int j = 0; j < len; ++j) {
            if (isupper(sentence[j])) {
                text[i][j] = tolower(sentence[j]);
            } else if (isdigit(sentence[j])) {
                text[i][j] = 'D';
            }
        }
    }
}


