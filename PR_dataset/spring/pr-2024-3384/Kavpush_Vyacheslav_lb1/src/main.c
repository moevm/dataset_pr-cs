#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define Block 20
#define Block_Count 10

char** input_text(int* len){ //Ввод текста
    size_t CharCnt = Block; //переменная для отслеживание выхода за границы выделенной памяти символов в предложении
    size_t WordsCnt = Block_Count; //переменная для отслеживание выхода за границы выделенной памяти предложений в массиве
    int i = 0; //счёт слов
    int j = 0; //счёт символов в слове
    int start = 1;
    char c;
    
    char** input = malloc(Block_Count * sizeof(char*));
    for (int l=0; l<Block_Count; l++)
        input[l] = calloc(Block, sizeof(char));
        
    while (1){
        if (i == WordsCnt){
            input = realloc(input, (WordsCnt + Block_Count) * sizeof(char*));
            for (int l=WordsCnt; l<(WordsCnt + Block_Count); l++){
                input[l] = calloc(Block, sizeof(char));
            }
            WordsCnt += Block_Count;
        }
        if (j == CharCnt){
            CharCnt += Block;
            input[i] = realloc(input[i], CharCnt * sizeof(char));
        }
        
        c = getchar();
        if (start==1){
            input[i][j] = c;
            j++;
            start = 0;
        }else{
            if((c=='\n') || (c==' ')){
                input[i][j] = '\0';
                start = 1;
                i++;
                j = 0;
                CharCnt = Block;
            }else{
                input[i][j] = c;
                if (strcmp(input[i], "Fin.") == 0){
                    input[i][j+1] = '\0';
                    break;
                }
                j++;
            }
        }
    }
    
    *len = i;
    return input;
}

int main() {
    char** text;
    int len = 0;
    char* regexString = "([a-z]+:\\/\\/)?(www\\.)?(([a-zA-Z0-9_]+\\.)+[a-zA-Z0-9_]+)(\\/)([a-zA-Z0-9_]+\\/)*([a-zA-Z0-9_]+\\.[a-zA-Z0-9_]+)";
    size_t maxGroups = 8;
    int start = 1;
    
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("Wow: no - can't compile regular expression");
        return 0;
    }
    
    text = input_text(&len);
    for(int i=0; i<len; i++){
        if(regexec(&regexCompiled, text[i], maxGroups, groupArray, 0) == 0){
            if (start == 1){
                start = 0;
                for (int j=groupArray[3].rm_so; j<groupArray[3].rm_eo; j++){
                    printf("%c",text[i][j]);
                }
                printf(" - ");
                for (int j=groupArray[7].rm_so; j<groupArray[7].rm_eo; j++){
                    printf("%c",text[i][j]);
                }
            }else{
                printf("\n");
                for (int j=groupArray[3].rm_so; j<groupArray[3].rm_eo; j++){
                    printf("%c",text[i][j]);
                }
                printf(" - ");
                for (int j=groupArray[7].rm_so; j<groupArray[7].rm_eo; j++){
                    printf("%c",text[i][j]);
                }
            }
        }
    }
    
    for (int i=0; i<len; i++){
        free(text[i]);
    }
    free(text);

    return 0;
}