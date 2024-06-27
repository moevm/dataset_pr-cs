#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Str {
    char* word;
} Str;

typedef struct Text {
    Str* Words;
    int count;
} Text;

void strsepar(char* in, Text* out) {
    char *token = strtok(in, " .");
    int i = 0;

    while(token) {
        int len = strlen(token);
        if (token[len - 1] == '\n') {
            len--;
            out->Words[i].word = (char*) malloc((len + 1) * sizeof(char));
            strncpy(out->Words[i].word, token, len);
            out->Words[i].word[len] = '\0';
        } else {
            out->Words[i].word = (char*) malloc((len + 1) * sizeof(char));
            strcpy(out->Words[i].word, token);
        }

        out->count = ++i;
        out->Words = (Str*) realloc(out->Words, (out->count + 1) * sizeof(Str));
        token = strtok(NULL, " ");
    }
}

int compare(const void* a, const void* b) {
    return strcmp((*(Str*)a).word, (*(Str*)b).word);
}

void strsort(Text* text) {
    qsort(text->Words, text->count, sizeof(Str), compare);
}

int strsearch(Text* text, Str* str) {
    if (bsearch(str, text->Words, text->count, sizeof(Str), compare)) {
        return 1;
    } else {
        return 0;
    }
}

void printresult(int isfind) {
    if (isfind) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
}

void myfree(Text* text, Str* str) {
    int count = text->count;
    for (int i = 0; i < count; ++i) {
        free(text->Words[i].word);
    }

    free(text->Words);
    free(text);
    free(str);
}

int main() {
    char textin[1000];
    char strin[30];

    fgets(textin, 1000, stdin);
    scanf("%s", strin);

    Text* text = (Text*) malloc(1 * sizeof(Text));
    text->Words = (Str*) malloc(1 * sizeof(Str));
    text->count = 0;

    Str* str = (Str*) malloc(1 * sizeof(Str));
    str->word = (char*) malloc((strlen(strin) + 1) * sizeof(char));
    strncpy(str->word, strin, strlen(strin));
    str->word[strlen(strin)] = '\0';

    strsepar(textin, text);
    strsort(text);
    printresult(strsearch(text, str));

    myfree(text, str);

    return 0;
}