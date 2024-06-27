#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EXTRA_MEM 100


char* read_sentence();

int main() {
    size_t Btop = 0;
    char** text = (char**)malloc(sizeof(char*));
    char* sentence;
    while(sentence = read_sentence()){
        text[Btop++] = sentence;
        text = (char**)realloc(text, sizeof(char*) * (Btop + 1));
        if(strcmp(sentence, "Dragon flew away!") == 0)
            break;
    }
    size_t Atop = 0;
    for(int i = 0; i < Btop; ++i){
        if(text[i][0] == '?'){
            free(text[i]);
        } else {
            Atop++;
            puts(text[i]);
            free(text[i]);
        }

    }
    printf("Количество предложений до %ld и количество предложений после %ld\n", Btop - 1, Atop - 1);
    return 0;
}

char* read_sentence(){
    char *sentence = (char*)malloc(sizeof(char));
    char c;
    int capacity = 1;
    int top = 0;
    while(c = getchar()){
        if(top >= capacity){
            capacity += EXTRA_MEM;
            sentence = (char*)realloc(sentence, capacity*sizeof(char));
        }
        if (top > 0 || c != ' ' && c != '\t' && c != '\n')
            sentence[top++] = c;
        if (c == '?'){
            sentence[0] = '?';
            break;}
        if (c == '.' || c == ';' || c == '!')
            break;
    }
    sentence[top] = '\0';
    return sentence;
}
