#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2000
#define M 32

int makeWordsArr(char **wordlist, char *word){
    char text[N];
    char sep[] = ". \n";
    int i = 0;

    fgets(text, N, stdin);
    scanf("%s", word);

    char *newWord = strtok (text, sep);

    while (newWord){
        wordlist[i++] = newWord;
        newWord = strtok (NULL, sep);
    }

    return i;
}

int comparator(const void *first, const void *second){
    const char **f = (const char **)first;
    const char **s = (const char **)second;
    return strcmp(*f, *s);
}

int comparatorForBinarySearch (const void *key, const void *val){
    const char *k = (const char *)key;
    const char **v = (const char **)val;
    return strcmp(k, *v);
}

void printRes(int *result){
    if (result){
        puts("exists");
    }
    else{
        puts("doesn't exist");
    }
}

int main() {
    char **wordlist = malloc(N * sizeof(char*));
    char *word = malloc(M * sizeof(char));
    int length = makeWordsArr(wordlist, word);

    qsort(wordlist, length, sizeof (char *), comparator);
    int *result = bsearch(word, wordlist, length, sizeof(char *), comparatorForBinarySearch);

    printRes(result);

    free(word);
    free(wordlist);

    return 0;
}
