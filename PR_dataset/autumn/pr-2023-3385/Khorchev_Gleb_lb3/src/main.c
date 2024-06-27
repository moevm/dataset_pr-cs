#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK 10

char* read_sentence();

int main(){
    char* sentence = read_sentence();
    int  counter = 1, counter_deleted = 0;
    while(1)
    {
    int str_len = strlen(sentence);
    char end_char = sentence[str_len-1];
    if (end_char == '.' || end_char == ';') printf("%s\n", sentence);
    else
        {
        if (end_char == '?') counter_deleted++;
        else
            {
            printf("%s\n", sentence);
            free(sentence);
            printf("Количество предложений до %d и количество предложений после %d\n", counter-1 , counter - counter_deleted-1);
            break;
            }
        }
    free(sentence);
    sentence = read_sentence();
    counter++;
    }

    return 0;
}

char* read_sentence(){

    size_t Capacity = BLOCK, len = 0;
    char* str =(char*)malloc(sizeof(char)*Capacity);
    char c = getchar();
    while(1)
    {
        if (c == '.' || c == ';' || c == '?' ||  c == '!'){
            str[len++] = c;
            getchar();
            break;
        }else{
            str[len++] = c;
            if(len == Capacity-1)
            {
                Capacity += BLOCK;
                str = (char*)realloc(str, Capacity);
                if (str == NULL){
                    fprintf(stderr, "realloc error\n");
                    break;
                }
            }
            c = getchar();
        }
    }
    str[len] = '\0';
    return str;
}
