#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define STEP 20
#define PATTERN "(\\w+)@[a-zA-Z0-9_-]+: ?~ ?# (.*)"
#define GROUPS 3

//функция освобождает память
void free_memory(char **text, int count_sents){
    for (int i = 0; i <= count_sents; i++){
        free(text[i]);
    }
    free(text);
}

//функция проверяет успешность выделения памяти
void validate_memory_allocation(char **text, int count_sents, void *ptr){
    if (ptr == NULL){
        free_memory(text, count_sents);
        fprintf(stderr, "Error: Memory Allocation Error\n");
        exit(0);
    }
}

//функция для считывания строк (посимвольно) и создания массива указателей на эти строки (разделитель \n)
char **read_text(int *count_sents){
    int i = 0, flag = 1;
    char currentChar;
    char **text = (char **)malloc(sizeof(char *));
    validate_memory_allocation(text, 0, text);
    text[0] = (char *)malloc(STEP * sizeof(char));
    validate_memory_allocation(text, 0, text[i]);
    while (flag){
        int j = 0, size = STEP;
        while(1){
            if (j % STEP == STEP - 1){
                size += STEP;
                text[i] = (char *)realloc(text[i], size * sizeof(char));
                validate_memory_allocation(text, i, text[i]);
            }
            currentChar = getchar();
            if (currentChar == '\n'){
                text[i][j+1] = '\0';
                break;
            }
            text[i][j] = currentChar;
            j++;
            text[i][j] = '\0';
            if ((strcmp(text[i], "Fin.\0") == 0) || currentChar == EOF){
                flag = 0;
                break;
            }
        }
        if (flag == 0){
            break;
        }
        i++;
        text = (char **)realloc(text, (i + 1) * sizeof(char *));
        validate_memory_allocation(text, i - 1, text);
        text[i] = (char *)malloc(STEP * sizeof(char));
        validate_memory_allocation(text, i - 1, text[i]);
    }
    *count_sents = i;
    return text;
}

//функция выводит подстроки из текста, соответствующие регулярному выражению
int process_text_with_regex(char **text, int count_sents){
    regex_t regex;
    int reti;
    regmatch_t pmatch[3];
    reti = regcomp(&regex, PATTERN, REG_EXTENDED); //компилируем регулярное выражение во внетреннее представление 
    if (reti) {
        fprintf(stderr, "Error: could not compile regex\n");
        free_memory(text, count_sents);
        regfree(&regex);
        return 1;
    }
    for (int counter = 0; counter <= count_sents; counter++){
        reti = regexec(&regex, text[counter], GROUPS, pmatch, 0);
        if (reti == 0){
            for (int p = pmatch[1].rm_so; p < pmatch[1].rm_eo; p++){
                printf("%c", text[counter][p]);
            }
            printf(" - ");
            for (int p = pmatch[2].rm_so; p < pmatch[2].rm_eo; p++){
                printf("%c", text[counter][p]);
            }
            printf("\n");
        }else if (reti && reti != REG_NOMATCH){
            fprintf(stderr, "Error: regex match failed");
            free_memory(text, count_sents);
            regfree(&regex);
            return 1;
        }
    }
    free_memory(text, count_sents);
    regfree(&regex);
    return 0;
}

//точка входа
int main(){
    char **text;
    int count_sents = 0, returnValue = 0;
    text = read_text(&count_sents);
    returnValue = process_text_with_regex(text, count_sents);
    return returnValue;
}
