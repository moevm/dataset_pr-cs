#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define N 2000

void writeAnswer(int* );
int cmp (const void* , const void* );
int cmpForBinarySearch (const void* , const void* );
int makeWordsArr(char** , char* );

void writeAnswer(int *answer){
    if (answer)
        puts("exists");
    else
        puts("doesn't exist");
}

int getCmp (const void *first, const void *second){
    const char **f = (const char **)first;
    const char **s = (const char **)second;
    return strcmp(*f, *s);
}

int cmpForBinarySearch (const void *key, const void *val){
    return strcmp((const char *)key, *(const char **)val);
}

int makeWordsArr(char **words, char *word){
    char text[N];
    char sep[] = ". \n";
    int j = 0;

    fgets(text, N, stdin);
    scanf("%s", word);

    char *istr = strtok (text,sep);

    while (istr){
        words[j++] = istr;
        istr = strtok (NULL,sep);
    }

    return j;
}

int main(){
    char **words = malloc(N*sizeof (char*));
    char *word = malloc(32*sizeof (char ));
    int n = makeWordsArr(words, word);

    qsort(words, n, sizeof (char *), getCmp);
    int *answer = bsearch(word, words, n, sizeof(char *), cmpForBinarySearch);

    writeAnswer(answer);

    free(word);
    free(words);

    return 0;
}
