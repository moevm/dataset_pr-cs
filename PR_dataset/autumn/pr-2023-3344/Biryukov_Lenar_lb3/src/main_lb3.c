#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INITIAL_SENTENCE_SIZE 100
#define CHUNK_SIZE 100

char* readSentence() {
    char* sentence = (char*)malloc(INITIAL_SENTENCE_SIZE * sizeof(char));
    int character = 1;
    int sentenceLength = 0;
    int maxSentenceLength = INITIAL_SENTENCE_SIZE;

    while (character != '.' && character != ';' && character != '!' && character != '?') {
        character = getchar();
        sentence[sentenceLength] = character;
        sentenceLength++;

        if (sentenceLength == maxSentenceLength) {
            maxSentenceLength += CHUNK_SIZE;
            sentence = (char*)realloc(sentence, maxSentenceLength);
        }
    }

    sentence[sentenceLength] = '\0';
    return sentence;
}

void removeLeadingSpace(char* sentence, int sentenceLength) {
    if (sentence[0] == '\t' || sentence[0] == ' ') {
        for (int i = 0; i < sentenceLength; i++) {
            sentence[i] = sentence[i + 1];
        }
    }
}

int containsDigits(char* sentence, int sentenceLength) {
    for (int i = 1; i < sentenceLength - 1; i++) {
        if ((isalpha(sentence[i - 1]) && isdigit(sentence[i]) && isalpha(sentence[i + 1])) ||
            (isdigit(sentence[i - 1]) && isdigit(sentence[i]) && isalpha(sentence[i + 1])) ||
            (isalpha(sentence[i - 1]) && isdigit(sentence[i]) && isdigit(sentence[i + 1]))) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char* sentence = "\0";
    int sentenceLength, numSentencesBefore, numSentencesAfter, numDeletedSentences;
    sentenceLength = numSentencesBefore = numSentencesAfter = numDeletedSentences = 0;

    while (strcmp(sentence, "Dragon flew away!")) {
        sentence = readSentence();
        sentenceLength = strlen(sentence);
        numSentencesBefore++;

        removeLeadingSpace(sentence, sentenceLength);

        if (containsDigits(sentence, sentenceLength)) {
            numDeletedSentences++;
            continue;
        }

        puts(sentence);
    }

    numSentencesAfter = numSentencesBefore - numDeletedSentences - 1;
    printf("Количество предложений до %d и количество предложений после %d", numSentencesBefore - 1, numSentencesAfter);

    free(sentence);
    return 0;
}
