#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int more_than_one_isupper(char *str);
int input(char** str);
int count_of_sentences(char *str);
char** treatment(char* str, int count_sentanses, int len);
void output(char** str, int count_sentences);
#define END '\0'

int input(char** str)
{
    int iter = 0;
    char c;
    while (1) {
            c = getchar();
            if(c == '!'){
                break;
            }
            if(c == '\n'){
                continue;
            }
            *str = (char *)realloc(*str, (iter + 1) * sizeof(char));
            *(*str + iter) = c;
            iter++;

    }
    *str = (char *)realloc(*str, (iter + 2) * sizeof(char));
    *(*str + iter) = c;
    iter ++;
    *(*str + iter) = END;
    return iter;
}
int main(){

    char* str = NULL;
    int len = input(&str);


    int count_sentences = count_of_sentences(str);
    

    char ** sentences = treatment(str, count_sentences,len);
    output(sentences, count_sentences);
    return 0;
}

void output(char** str, int count_sentences){
    int count = 0;
    for(int k = 0;k < count_sentences;k++){
        if (more_than_one_isupper(str[k])){
            printf("%s\n", str[k]);
            count ++;
        }
    }
    printf("Количество предложений до %d и количество предложений после %d",count_sentences - 1,count - 1);


    for (int i = 0; i < count_sentences; i++) {
        free(str[i]);
    }

    free(str);


}






char** treatment(char* str, int count_sentanses, int len){
    char ** result = malloc(sizeof(char*) * count_sentanses);
    int number = 0;
    int index_last_symbol = 0;
    int size_sentence = 1;
    char* sentence = malloc(sizeof(char) * size_sentence);
    for(int i = 0; i < len;i++){
        sentence[index_last_symbol++] = str[i];
        sentence = realloc(sentence, sizeof(char) * (size_sentence + 1)) ;
        size_sentence++;
        if(str[i] == '.' || str[i] == ';' || str[i] == '?' || str[i] == '!'){
            sentence[index_last_symbol] = END;
            if (sentence[0] == ' '){
                memmove(sentence, sentence + 1, strlen(sentence));
            }
             result[number] = strdup(sentence);
             number++;
             free(sentence);
             sentence = malloc(0);
             size_sentence = 1;
             index_last_symbol = 0;
            
        }

    }
    return result;
}
int count_of_sentences(char *str)
{
    int count = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '.' || str[i]  == ';' || str[i]  == '?' || str[i]  == '!'){
            count ++;
        }

    }
    return count;


}

int more_than_one_isupper(char *str){

    int count = 0;
    for(int i = 0; i < strlen(str); i++){
        if(isupper(str[i])){
            count ++;
            if(count == 2){
                return 0;
            }
        }
    }

    return 1;

}
