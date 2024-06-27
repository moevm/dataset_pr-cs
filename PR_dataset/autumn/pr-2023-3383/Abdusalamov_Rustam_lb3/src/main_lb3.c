#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SENTENCES 170
#define MAX_WORDS 80

int without7(char* sentence) {
    for (int j = 0; sentence[j]; j++) {
        if (sentence[j] == '7') {
            return 0;
        }
    }
    return 1;
}

void find_and_print_sentences(char *text, const char *terminators) {
    char **sentences = calloc(MAX_SENTENCES, sizeof(char*));
    int sent_before = 0;
    int sent_after = 0; 
    int index = 0;
    for (int i = 0; text[i]; i++) {
        if (strchr(terminators, text[i])) {
            sentences[sent_after] = malloc(sizeof(char) * (i - index + 2));
            for (int j = 0; j < (i - index + 1); j++) {
                sentences[sent_after][j] = text[index + j];
            }
            sentences[sent_after][i - index + 1] = '\0';
            if (without7(sentences[sent_after])) {
                sent_after++;
            }
            sent_before++;
            index = i + 2;
        }
    }
    for (int i = 0; i < sent_after; i++) {
        printf("%s\n", sentences[i]);
        free(sentences[i]);
    }
    free(sentences);
    printf("Количество предложений до %d и количество предложений после %d\n", sent_before - 1, sent_after - 1); // Заменено nbefore и nafter на sent_before и sent_after
   
}
int main() {
    char *text = malloc(MAX_SENTENCES * MAX_WORDS);
    const char terminators[] = ".?;!";
    fgets(text, MAX_SENTENCES * MAX_WORDS, stdin);
    find_and_print_sentences(text, terminators);
    free(text);
    return 0;
}