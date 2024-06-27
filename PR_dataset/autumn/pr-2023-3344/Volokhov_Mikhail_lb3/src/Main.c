#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int containsDigit(const char *word) {
    int length = strlen(word);

    int firstIndex = -1;
    int lastIndex = -1;

    // Finds the first character
    for (int i = 0; i < length; i++) {
        if (isalpha(word[i])) {
            firstIndex = i;
            break;
        }
    }

    if (firstIndex == -1) {
        return 0;
    }

    // Finds the last character
    for (int j = length - 1; j >= 0; j--) {
        if (isalpha(word[j])) {
            lastIndex = j;
            break;
        }
    }

    // Check presence of a digit within the range
    for (int i = firstIndex; i <= lastIndex; i++) {
        if (isdigit(word[i])) {
            return 1;
        }
    }

    return 0;
}

int splitSentence(char *sentence) {
    char separator[] = " ";
    char *word = strtok(sentence, separator);

    while (word != NULL) {
        if (containsDigit(word)) {
            return 1;
        }
        word = strtok(NULL, separator);
    }

    return 0;
}

void formatSentence(char *sentence) {
    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] == '\t') {
            sentence[i] = ' ';
        }
    }

    if (sentence[0] == ' ') {
        memmove(sentence, sentence + 1, strlen(sentence));
    }
}

int main() {
    char **text = (char **)malloc(1 * sizeof(char *));
    char *currentSentence = malloc(1 * sizeof(char));
    int formatted_sentence_count = 0;
    int original_sentence_count = 0;
    char symbol;

// Main Loop
do {
    int symbolCount = 0;

    // Read characters until an end symbol
    do {
        symbol = getchar();
        currentSentence[symbolCount] = symbol;
        symbolCount++;
        currentSentence = realloc(currentSentence, (symbolCount + 1) * sizeof(char));// Resize memory
    } while (symbol != '.' && symbol != ';' && symbol != '!' && symbol != '?');

    currentSentence[symbolCount++] = '\0'; 
    char *temp = (char *)malloc(symbolCount * sizeof(char));
    strcpy(temp, currentSentence);  // Create a temporary copy of the current sentence

    // Check for a digit if not, formatting
    if (splitSentence(temp) == 0) {
        formatSentence(currentSentence);
        text[formatted_sentence_count] = currentSentence;
        formatted_sentence_count++;
        text = realloc(text, (formatted_sentence_count + 1) * sizeof(char *));
    }
    if (strstr(currentSentence, "Dragon flew away!")) {
        break;
    }

    original_sentence_count++;
    currentSentence = malloc(1 * sizeof(char));  // Allocating memory for the next sentence
} while(!strstr(currentSentence, "Dragon flew away!"));


    for (int i = 0; i < formatted_sentence_count; i++) {
        printf("%s\n", text[i]);
    }

    printf("Количество предложений до %d и количество предложений после %d\n", original_sentence_count, formatted_sentence_count-1);

    free(currentSentence);
    free(text);

    return 0;
}
