#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

struct answer{
    char nameOfWebsite[100];
    char nameOfFile[100];
};

struct answer createAnswer(){
    struct answer newAnswer;

    newAnswer.nameOfWebsite[0] = '\0';
    newAnswer.nameOfFile[0] = '\0';

    return newAnswer;
}

void memoryError(){
    printf("Memory allocation error!");
    exit(0);
}

int main(){
    char * regexString = "(:\\/\\/)?(www\\.)?([a-zA-Z0-9\\.]+)\\/([a-zA-Z0-9\\.]+\\/?)+";
    size_t maxGroups = 5;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if(regcomp(&regexCompiled, regexString, REG_EXTENDED) ){
        printf("cant compile regex(");
        return 0;
    }


    struct answer *answerArray = NULL;
    size_t quantityOfAnswer = 0;

    char text[100];

    while (1) {
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0';

        if(regexec(&regexCompiled, text, maxGroups, groupArray, 0) == 0){
            struct answer newAnswer = createAnswer();
            size_t isDotInName = 0;
            size_t isDotInFile = 0;
            for (int i = 0; i <= maxGroups; i++) {
                if(groupArray[i].rm_so == -1){
                    continue;
                }

                if(i == 3){
                    for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++) {
                        if(text[j] == '.'){
                            isDotInName = 1;
                        }
                        strncat(newAnswer.nameOfWebsite, &text[j], 1);
                    }
                }

                if(i == 4){
                    for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++) {
                        if(text[j] == '.'){
                            isDotInFile = 1;
                        }
                        strncat(newAnswer.nameOfFile, &text[j], 1);
                    }
                }
            }

            if(isDotInName && isDotInFile){
                answerArray = realloc(answerArray, sizeof(struct answer) * (quantityOfAnswer + 1));
                if(answerArray == NULL){
                    memoryError();
                }

                answerArray[quantityOfAnswer] = newAnswer;
                quantityOfAnswer++;
            }
        }

        if (strcmp(text, "Fin.") == 0) {
            break;
        }

    }

    for (int i = 0; i < quantityOfAnswer; i++) {
        printf("%s - %s\n", answerArray[i].nameOfWebsite, answerArray[i].nameOfFile);
    }
    free(answerArray);
    regfree(&regexCompiled);

    return 0;
}