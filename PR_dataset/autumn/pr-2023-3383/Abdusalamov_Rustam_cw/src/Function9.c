#include "Common.h"
#include "Function9.h"
#include "FreeMemory.h"

int digitsSum(char* word){
    int len = strlen(word);
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        if (isdigit(word[i]))
        {
            int digit = word[i] - '0';
            sum += digit;
        }
    }
    return sum;
}

int compare1(const void* a, const void* b)
{
    char* word1 = *(char**)a;
    char* word2 = *(char**)b;
    int sum1 = digitsSum(word1);
    int sum2 = digitsSum(word2);
    return sum1 - sum2;
}

char** splitWords(char* sentence, int* wordCount) {
    const char delimiters[] = " ,.";
    char** words = NULL;
    char* token = strtok(sentence, delimiters);
    *wordCount = 0;
    while (token != NULL) {
        (*wordCount)++;
        words = realloc(words, (*wordCount) * sizeof(char*));
        if (words == NULL) {
            return NULL;
        }
        words[(*wordCount) - 1] = strdup(token);
        token = strtok(NULL, delimiters);
    }
    return words;
}

void Function9(char** text, int sentences_count)
{
    for (int i = 0; i < sentences_count; i++)
    {
        char* sentence = text[i];
        int words_count = 0;
        char** words = splitWords(sentence, &words_count);
        qsort(words, words_count, sizeof(char*), compare1);
        for (int j = 0; j < words_count; j++)
        {
            if(j == words_count - 1)
                printf("%s.", words[j]);
            else
                printf("%s ", words[j]);
        }
        printf("\n");
        FreeMemory(words,words_count);
    }
}
