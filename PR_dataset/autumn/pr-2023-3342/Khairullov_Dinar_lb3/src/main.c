#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define STR_OUTPUT "Количество предложений до %d и количество предложений после %d"
#define STR_OUTPUT_SEG "%s\n"
#define NULL_STR '\0'

char **text_input(int *num_of_sen){
    char **text;
    *num_of_sen = 1;
    int num_of_sym = 1;
    text = malloc((*num_of_sen)*sizeof(char*));
    text[0] = malloc(num_of_sym*sizeof(char));
    char sym;
    while(1){
        sym = getchar();
        if(sym == '.' || sym == ';' || sym == '?'){
            text[(*num_of_sen)-1][num_of_sym-1] = sym;
            text[(*num_of_sen)-1] = realloc(text[(*num_of_sen)-1],(num_of_sym+1)*sizeof(char));
            text[(*num_of_sen)-1][num_of_sym] = NULL_STR;
            *num_of_sen += 1;
            num_of_sym = 1;
            text = realloc(text, (*num_of_sen)*sizeof(char*));
            text[(*num_of_sen)-1] = malloc(num_of_sym*sizeof(char));
            continue;
        }
        if((sym == '\t') || (sym == '\n')){
            continue;
        }
        //
        if(sym == ' ' && (num_of_sym-1) == 0){
            continue;
        }
        //
        if(sym == '!'){
            text[(*num_of_sen)-1][num_of_sym-1] = sym;
            text[(*num_of_sen)-1] = realloc(text[(*num_of_sen)-1],(num_of_sym+1)*sizeof(char));
            text[(*num_of_sen)-1][num_of_sym] = NULL_STR;
            break;
        }
        text[(*num_of_sen)-1][num_of_sym-1] = sym;
        num_of_sym +=1;
        text[(*num_of_sen)-1] = realloc(text[(*num_of_sen)-1], (num_of_sym*sizeof(char)));
    }
    return text;
}

void text_output(int num_of_sen, char**text){
    int upper_counter = 0;
    int sym_counter = 0;
    int sen_after = 0;
    for(int counter = 0; counter < num_of_sen; counter++){
        while(1){
            if(isupper(text[counter][sym_counter])){
                upper_counter +=1;
                sym_counter +=1;
                continue;
            }
            else if(text[counter][sym_counter]  == NULL_STR){
                sym_counter = 0;
                break;
            }
            sym_counter +=1;
        }
        if(upper_counter <= 1){
            printf(STR_OUTPUT_SEG, text[counter]);
            sen_after +=1;
        }
        upper_counter = 0;
    }
    printf(STR_OUTPUT, num_of_sen-1, sen_after-1);
    
}

void clean_mem(char **text, int num_of_sen){
    for(int i = 0; i<num_of_sen; i++){
        free(text[i]);
    }
    free(text);
}

int main(){
    int number_of_sen = 0;
    int *p_number_of_sen = &number_of_sen;
    
    char **prefinal_text = text_input(p_number_of_sen);
    
    text_output(number_of_sen, prefinal_text);
    
    clean_mem(prefinal_text, number_of_sen);
    
    return 0;
    
}