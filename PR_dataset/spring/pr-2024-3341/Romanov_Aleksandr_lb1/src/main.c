#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

char* InputText(int* number_of_sentences);
char** Split(char* text, int* number_of_sentences);
void Result(char** sentences, int* number_of_sentences);
void ResultSite(char** sentences, int* number_of_sentences);

int main(){

    int number_of_sentences = 0;
    char* text = InputText(&number_of_sentences);

    char** sentences = Split(text, &number_of_sentences);
    Result(sentences, &number_of_sentences);
    free(text);
    
    for (int i = 0; i < number_of_sentences; i++){
    	free(sentences[i]);
    }
    
    free(sentences);
}

char* InputText(int* number_of_sentences){

    char* text = (char*)malloc(sizeof(char));

    char end_of_text[5] = "Fill";
    char symbol = getchar();

    int position = 0;
    int capacity = 1;

    while (1==1){
        text[position] = symbol;

        if(position+1 >= capacity){
            capacity *= 2;
            text = (char*)realloc(text, capacity * sizeof(char));
        }

        if(symbol == '\n'){
            (*number_of_sentences)++;
        }

        position++;


        for(int i = 0; i < 3; i++){
            end_of_text[i] = end_of_text[i+1];
        }

        end_of_text[3] = symbol;

        if(strncmp(end_of_text, "Fin.", 4) == 0){
            text[position] = '\0';
            break;
        }

        symbol = getchar();
    }
    return text;
}

char** Split(char* text, int* number_of_sentences){
    char** sentences = (char**)malloc((*number_of_sentences)*sizeof(char*));

    int position = 0;
    int start = 0;
    int end = 0;

    for(int i = 0; i < strlen(text); i++){

        if(text[i]=='\n'){

            end = i;

            int pos = 0;
            
            sentences[position] = (char*)malloc(sizeof(char)*(end-start+1));

            for(int j = start; j <= end; j++){
                sentences[position][pos] = text[j];
                pos++;
            }

            sentences[position][pos] = '\0';

            position++;

            if (end + 1 < strlen(text)){
                start = end + 1;
            }
            else{
                break;
            }
        }

    }

    return sentences;
}

void Result(char** sentences, int* number_of_sentences){
    int flag = 0;

    char mask[] = "([A-Za-z0-9_]+)@[A-Za-z0-9_-]+: *?~ *?# (.*\n)";
    size_t groups = 3; 

    regex_t mask_compiled;
    regmatch_t arr[groups];

    if (regcomp(&mask_compiled, mask, REG_EXTENDED)){
        printf("Error: could not compile regular expression\n");

    }

    for(int i = 0; i < (*number_of_sentences); i++){
        if(regexec(&mask_compiled, sentences[i], groups, arr, 0) == 0){

            if(flag != 0){
                printf("\n");
            }
            else{
                flag = 1;
            }

            for(int x = arr[1].rm_so; x < arr[1].rm_eo; x++){
                printf("%c", sentences[i][x]);
            }

            printf(" - ");

            for(int x = arr[2].rm_so; x < arr[2].rm_eo-1; x++){
                printf("%c", sentences[i][x]);
            }
        }
    }
}

