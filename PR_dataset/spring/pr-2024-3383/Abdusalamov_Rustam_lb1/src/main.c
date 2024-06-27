#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_SENT 100
#define STR_LEN 100
#define MAX_MATCHES 7

int readText(char **text) {
    char sentence[STR_LEN];
    int sentences_count = 0;
    int index = 0;
    char c;
    int flag = 0;

    while (!flag) {
        c = getchar();
        if (c == '\n' || c == EOF){
            sentence[index] = '\n';
            sentence[index+1] = '\0';
            text[sentences_count] = malloc((strlen(sentence) + 1) * sizeof(char));
            strcpy(text[sentences_count], sentence);
            sentences_count++;
            index = 0;

            if (strcmp(sentence, "Fin.\n") == 0) {
                flag = 1; 
            } 
        } else {
            sentence[index] = c;
            index++;
        }
    }
    return sentences_count;
}

int main() {
    char **text = malloc(MAX_SENT * sizeof(char *));
    char **sites = malloc(MAX_SENT * sizeof(char *));
    char **files = malloc(MAX_SENT * sizeof(char *));
    int sentences_count = readText(text);
    char* pattern = "([a-zA-z]+://)?(w{3}\\.)?(\\w+\\.\\w+(\\.\\w+)*)/(\\w+/)*(\\w+\\.\\w+)";
    regex_t regex;
    int count = 0;
    regcomp(&regex, pattern, REG_EXTENDED);
    for (int i = 0; i < sentences_count; i++) 
    {
        regmatch_t matches[MAX_MATCHES];
        if (regexec(&regex, text[i], MAX_MATCHES, matches, 0) == 0) {
            // Первая группа
            int match_length = matches[3].rm_eo - matches[3].rm_so;
            char match_group1[STR_LEN];
            strncpy(match_group1, text[i] + matches[3].rm_so, match_length);
            match_group1[match_length] = '\0';
            sites[count] = malloc(match_length+1);
            strcpy(sites[count],match_group1);
            // Вторая группа
            match_length = matches[6].rm_eo - matches[6].rm_so;
            char match_group2[STR_LEN];
            strncpy(match_group2, text[i] + matches[6].rm_so, match_length);
            match_group2[match_length] = '\0';
            files[count] = malloc(match_length+1);
            strcpy(files[count],match_group2);
            count++;
        }
    }
    for(int i = 0; i < count; i++){
        printf("%s - %s",sites[i],files[i]);
        if (i!=count-1)
        printf("\n");
    }
    return 0;
}