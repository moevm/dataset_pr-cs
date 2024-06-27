#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 10
#define LAST_SENTENCE "Dragon flew away!"
#define OUTPUT "Количество предложений до %d и количество предложений после %d"
#define STR_OUTPUT "%s\n"
#define END_OF_STR '\0'
char** input_text(int* current_element, int* current_last_sentence,char** text,int* final_quantity_of_sentences){
    int excess_of_letters=0;
    int excess_of_sentences=0;
char* sentence=(char*)malloc(SIZE*sizeof(char));
    while(1){
        char letter=getchar();
        sentence[(*current_element)] = letter;
        (*current_element)++;
        if((SIZE + excess_of_letters)<=(*current_element)){
            excess_of_letters++;
            sentence = (char*)realloc(sentence,(SIZE + excess_of_letters)*sizeof(char));
        }
        if(strstr(sentence,LAST_SENTENCE)!=NULL){
            text[(*current_last_sentence)]=LAST_SENTENCE;
            (*current_last_sentence)++;
            break;
        }
        if(letter=='.'||letter=='?'||letter==';'){
            sentence[*current_element]=END_OF_STR;
            text[(*current_last_sentence)]=sentence;
            (*current_last_sentence)++;
            (*current_element)=0;
            excess_of_letters=0;
            sentence=(char*)malloc(SIZE*sizeof(char));
        }
        if((SIZE+excess_of_sentences)<=(*current_last_sentence)){
           excess_of_sentences++;
            text=(char**)realloc(text,(SIZE+excess_of_sentences)*sizeof(char*));
            text[(SIZE+excess_of_sentences)-1]=(char*)malloc(SIZE*sizeof(char));
        }
    }
    free(sentence);
    return text;
}
char** new_text(){
    char** text=(char**)malloc(SIZE*sizeof(char*));
    for(int current_sentence=0;current_sentence<SIZE;current_sentence++){
        text[current_sentence]=(char*)malloc(SIZE*sizeof(char));
    }
    return text;
}
char* delete_tab(char* sentence){
    int element=0;
    while(sentence[element]=='\t'||sentence[element]==' '){
        element++;
    }
    char* text_without_tabs = strdup(sentence+element);
    return text_without_tabs;
}

int delete_sentences_with_seven(char* sentence){
    int length_of_sentence=strlen(sentence);
    for(int element=0; element<length_of_sentence;element++){
        if(sentence[element]=='7'){
            return false;
        }
    }
    return true;
}
void output_text(int* current_last_sentence,char** text,int* final_quantity_of_sentences){
    for(int current_sentence=0;current_sentence<(*current_last_sentence)-1;current_sentence++){
        char* new_text=delete_tab(text[current_sentence]);
        if(delete_sentences_with_seven(new_text)){
            (*final_quantity_of_sentences)++;
            printf(STR_OUTPUT,new_text);
        }
        free(new_text);
    }
    printf(STR_OUTPUT,LAST_SENTENCE);
}
int main()
{
    char** text= new_text();
    int element =0;
    int* current_element=&element;
    int final=0;
    int* final_quantity_of_sentences=&final;
    int current_last=0;
    int* current_last_sentence=&current_last;
    text=input_text(current_element,current_last_sentence,text,final_quantity_of_sentences);
    output_text(current_last_sentence,text,final_quantity_of_sentences);
    for (int current_sentence=0;current_sentence<current_last-1;current_sentence++){
         free(text[current_sentence]);
    }
    free(text);
    printf(OUTPUT, current_last-1, final);
    return 0;
}

