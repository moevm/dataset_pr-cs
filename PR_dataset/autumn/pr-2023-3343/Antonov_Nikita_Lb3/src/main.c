#include<locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char* input(int* before, char* last_sim){
    int size = 100;
    int length = 0;
    char sim;
    char* input = (char*)malloc(sizeof(char) * size);
    while((sim = getchar()) != *last_sim){
        if((sim != '\n') && (sim != '\t')){
            if(length >= size){
                size *= 2;
                input = (char*)realloc(input, size * sizeof(char));
            }
            if((sim == '.') || (sim == ';') || (sim == '?')){
                (*before)++;
            }
            input[length++] = sim;
        }
    }
    input = (char*)realloc(input, (length + 2) * sizeof(char));
    input[length] = *last_sim;
    input[length + 1] = '\0';
    return input;
}


char** splitText(char* input, char* splits, int* after){
    int sentences_counter = 0;
    int id = 0;
    int switcher = 0;
    char** sentences = (char**)malloc(sizeof(char*));
    for(int i = 0; i < strlen(input); i++){
        if(input[i] == '7'){
            switcher = 1;
        }
        if(strchr(splits, input[i])){
            if(switcher == 1){
                switcher = 0;
                id = 0;
                continue;
            }
            sentences_counter++;
            sentences = (char**)realloc(sentences, sentences_counter * sizeof(char*));
            sentences[sentences_counter - 1] = (char*)malloc((id + 2) * sizeof(char));
            int temp_const = 0;
            for(int j = id; j >= 0; j--){
                if(j == id && input[i - j] == ' ')
                    continue;
                sentences[sentences_counter - 1][temp_const++] = input[i - j];
            }
            sentences[sentences_counter - 1][temp_const] = '\0';
            id = 0;
            continue;
        }
        id++;
    }
    *after = sentences_counter - 1;
    return sentences;
}


int main(){
    setlocale(LC_ALL, "RU");
    int after = 0, before = 0;
    char last_sim = '!';
    char splits[] = ";.?!";
    char* input_text = input(&before, &last_sim);
    char** new_sentences = splitText(input_text, splits, &after);
    for(int i = 0; i < after; i++){
        printf("%s\n", new_sentences[i]);
        free(new_sentences[i]);
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d\n", before, after);
    free(input_text);
    free(new_sentences);
    return 0;
}