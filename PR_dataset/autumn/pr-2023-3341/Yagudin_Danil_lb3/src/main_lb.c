#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define END_SENT '\0'

char* read_text(int* len, int* sent_before) {

    int capacity = 1;
    char* text = (char*) malloc(sizeof(char));
    char ch = getchar();

    while (ch != '!') {
        text[(*len) - 1] = ch;
        if ((*len) >= capacity) {
            capacity *= 2;
            text = (char*)realloc(text, capacity * sizeof(char));
        }
        (*len) ++;
        if (ch == '.' || ch == ';' || ch == '?') {
            (*sent_before) ++;
        }
        ch = getchar();
    }

    return text;

}

void get_punkt(char *punkt, char *text, int len){

    int j = 0;

    for (int i = 0; i < len; i ++){
        if (text[i] == '.' || text[i] == ';' || text[i] == '?'){
            punkt[j ++] = text[i];
        }
    }

} 

char* cleaner(char *str, int len){

    char *new_str = malloc(sizeof(char) * len);
    int i = 0, j = 0, up_count = 0, p = 0;
    if (str[0] == ' ' || str[0] == '\n'){
        i = 1;
        p = 1;  
    }

    for (; p < len; p ++){
        if (isupper(str[p])){
            up_count ++;
        }
    }

    if (up_count >= 2){
        new_str[0] = END_SENT; 
    }else{
        for (; i < len; i ++){
            if (str[i] != '\n'){
                new_str[j ++] = str[i];
            }
        }
        new_str[j] = END_SENT;
    }

    return new_str;

}

void separate(char *text, char **separate_str){

    int i = 0;
    char *sep = "?.;";
    char *str = strtok(text, sep);

    while(str != NULL){
        separate_str[i] = malloc(sizeof(char) * strlen(str) + 1);
        separate_str[i ++] = cleaner(str, strlen(str) + 1);
        
        str = strtok(NULL, sep);
    }
    
}

void out(char **separate_str, char *punkt, int sent_before){
    int zero_sent = 0;

    for (int i = 0; i < sent_before; i ++){
        int j = 0;
        if (separate_str[i][j] != END_SENT){
            while(separate_str[i][j] != END_SENT){
                printf("%c", separate_str[i][j]);
                j ++;
            }
            printf("%c\n", punkt[i]);
        }else{
            zero_sent ++;
        }
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d", sent_before, sent_before - zero_sent);

}

int main(){

    int len = 1, sent_before = 0; 
    char *text = read_text(&len, &sent_before);

    char *punkt = (char*)malloc(sent_before * sizeof(char));
    get_punkt(punkt, text, len);

    char **separate_str = malloc(sizeof(char*) * sent_before);
    separate(text, separate_str);

    out(separate_str, punkt, sent_before);
     
    return 0;

}
