#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define EXTRA_BUF 50

char* readSentence(){
    char *tmp = (char*)malloc(sizeof(char));
    char *sentence;
    if (tmp) {
        sentence = tmp;
        tmp = NULL;
    }
    char c;
    int capacity = 1;
    int len = 0;
    while((c = getchar())){
        if(len >= capacity){
            capacity += EXTRA_BUF;
            tmp = (char*)realloc(sentence, capacity*sizeof(char));
            if (tmp){
                sentence = tmp;
                tmp = NULL;
            }
        }

        if (c == '.') {
            sentence[len] = '.';
            sentence[len + 1] = '\0';
            if (strcmp(sentence, "Fin.") == 0)
                return sentence;
            else {
                sentence[len + 1] = ' ';
            }
        }

        if (len >= 1 || (c != ' ' && c != '\t' && c != '\n'))
            sentence[len++] = c;

        if (c == '\n')
            break;
    }
    sentence[len] = '\0';
    return sentence;
}

char** readText(int *size){
    char **text = (char**)malloc(sizeof(char*));
    char *s;
    int count = 0;
    while((s = readSentence())){
        text[count++] = s;
        text = (char**)realloc(text, sizeof(char*)*(count+1));
        if (strcmp(s, "Fin.") == 0)
            break;
    }
    *size = count;
    return text;
}

int main ()
{
    int size;
    char **text = readText(&size);
    char * regexString = "([a-z]+:\\/{2}|)(www\\.|)(([a-zA-Z0-9][a-zA-Z0-9-]*\\.)+)([a-zA-Z0-9-]+)\\/([a-zA-Z0-9_-]+\\/)*([a-zA-Z0-9_-]+\\.[a-zA-Z0-9_-]+)";
    size_t maxGroups = 8;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Сan't compile regular expression\n");
        return 0;
    };
    int flag = 0;
    for (int k = 0;k < size; k++){
        if (regexec(&regexCompiled, text[k], maxGroups, groupArray, 0) == 0)
        {   
            
            if (flag > 0) {
                printf("\n");
            }
            flag++;
            for(int j=groupArray[3].rm_so;j<groupArray[3].rm_eo;j++)
                printf("%c",text[k][j]);
            for(int j=groupArray[5].rm_so;j<groupArray[5].rm_eo;j++)
                printf("%c",text[k][j]);
            printf(" - ");
            for(int j=groupArray[7].rm_so;j<groupArray[7].rm_eo;j++)
                printf("%c",text[k][j]);
                
        }
        free(text[k]);
    }
    free(text);
    regfree(&regexCompiled);

    return 0;
}
