#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_TEXT_LEN = 1000;
const int MAX_WORD_LEN = 30;

int comparator(const void* a, const void* b) {
    return strcmp((char*)a, (char*)b);
}

int read_words(char words[][MAX_WORD_LEN + 1]) {
    int n = 0;
    char text[MAX_TEXT_LEN + 1];
    fgets(text, MAX_TEXT_LEN + 1, stdin);
    const char delimiters[] = " .\n\"()";
    char* token = strtok(text, delimiters);
    while (token != NULL) {
        strcpy(words[n], token);
        ++n;
        token = strtok(NULL, delimiters);
    }
    return n;
}

void write_result(const void* found) {
    puts(found? "exists" : "doesn't exist");
}

int main() {
    char words[(MAX_TEXT_LEN + 1) / 2][MAX_WORD_LEN + 1];

    int n = read_words(words);

    // Find Word
    qsort(words, n, MAX_WORD_LEN + 1, comparator);
    char word[MAX_WORD_LEN + 1];
    scanf("%s", word);
    const void* found = bsearch(word, words, n, MAX_WORD_LEN + 1, comparator);

    write_result(found);
}
