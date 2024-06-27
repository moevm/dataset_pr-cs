#include "Function1.h"
#include "Common.h"
#include "FreeMemory.h"

char** Function1(char** text, int* sentences_count)
{
    int new_count = 0;
    char** new_text = (char**)malloc(*sentences_count * sizeof(char*));
    if (new_text == NULL)
        return NULL;
    for (int i = 0; i < *sentences_count; i++)
    {
        if (strstr(text[i], "banana ") || strstr(text[i], "apple ") || strstr(text[i], "apple,") || strstr(text[i], "banana,") || strstr(text[i], "apple.") || strstr(text[i], "banana."))
        {
            char* sentence = text[i];
            char* word = strtok(sentence, " .");
            int memory = strlen(sentence);
            char* new_sentence = (char*)malloc(memory * sizeof(char));
            if (new_sentence == NULL)
                return NULL;
            new_sentence[0] = '\0';
            while (word != NULL) {
                while(strlen(new_sentence) + strlen(word) + 10 >= memory)
                {
                    memory += MEM_STEP;
                    new_sentence = realloc(new_sentence, memory * sizeof(char));
                }
                if (strcmp(word, "banana,") == 0) {
                    strcat(new_sentence, "\033[1;33m");
                    strcat(new_sentence, "banana");
                    strcat(new_sentence, "\033[0m, ");
                }
                else if (strcmp(word, "banana") == 0) {
                    strcat(new_sentence, "\033[1;33m");
                    strcat(new_sentence, word);
                    strcat(new_sentence, "\033[0m ");
                }
                else if (strcmp(word, "apple,") == 0) {
                    strcat(new_sentence, "\033[1;32m");
                    strcat(new_sentence, "apple");
                    strcat(new_sentence, "\033[0m, ");
                }
                else if (strcmp(word, "apple") == 0) {
                    strcat(new_sentence, "\033[1;32m");
                    strcat(new_sentence, word);
                    strcat(new_sentence, "\033[0m ");
                }
                else {
                    strcat(new_sentence, word);
                    strcat(new_sentence, " ");
                }
                word = strtok(NULL, " .");
            }
            int len = strlen(new_sentence);
            new_sentence[len - 1] = '.';
            new_sentence[len] = '\0';
            new_text[new_count] = (char*)malloc(len * sizeof(char));
            if (new_text[new_count] == NULL)
                return NULL;
            strcpy(new_text[new_count], new_sentence);
            free(new_sentence);
            new_count++;
        }
    }
    FreeMemory(text, *sentences_count);
    *sentences_count = new_count;
    return new_text;
}
