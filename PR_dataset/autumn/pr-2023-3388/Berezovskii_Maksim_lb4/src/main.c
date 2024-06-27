#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_MAIN_TEXT 1001
#define MAX_LEN_WORD_TO_FIND 31

int split(char ***array_words_from_main_text, char **word_to_find) {
    char main_text[MAX_LEN_MAIN_TEXT];
    fgets(main_text, MAX_LEN_MAIN_TEXT, stdin);

    char sep[] = " .\n";
    main_text[strcspn(main_text, "\n")] = '\0';

    *word_to_find = malloc(MAX_LEN_WORD_TO_FIND * sizeof(char));
    scanf("%s", *word_to_find);

    char *istr;
    istr = strtok(main_text, sep);
    int i = 0;
    while (istr != NULL) {
        (*array_words_from_main_text)[i] = strdup(istr);
        i++;
        istr = strtok(NULL, sep);
    }
    int length = i;
    *array_words_from_main_text = realloc(*array_words_from_main_text, length * sizeof(char *));

    return length;
}

int comparator_to_qsort(const void *a, const void *b) {
    const char * const *first = (const char * const *) a;
    const char * const *second = (const char * const *) b;

    return strcmp(*first, *second);
}

int comparator_to_bsearch(const void *key, const void *val) {
    const char *k = (const char *) key;
    const char * const *v = (const char * const *) val;

    return strcmp(k, *v);
}

void res(const char *result) {
    printf("%s\n", result ? "exists" : "doesn't exist");
}

void key_function() {
    char **array_words_from_main_text = malloc(MAX_LEN_MAIN_TEXT * sizeof(char *));
    char *word_to_find;

    int length = split(&array_words_from_main_text, &word_to_find);

    qsort(array_words_from_main_text, length, sizeof(char *), comparator_to_qsort);

    char *result = bsearch(word_to_find, array_words_from_main_text, length, sizeof(char *), comparator_to_bsearch);
    res(result);

    for (int i = 0; i < length; i++) {
        free(array_words_from_main_text[i]);
    }
    free(array_words_from_main_text);
    free(word_to_find);
}

int main() {
    key_function();

    return 0;
}
