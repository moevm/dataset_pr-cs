#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* input(){
    int size = 100;
    int len = 0;
    int c;
    char *sent = malloc(size);

    while(1){
        c = getchar();
        sent[len++] = c;

        if(c =='!' || c == '.' || c == ';' || c == '?')
            break;

        if(len == size){
            size += 100;
            sent = realloc(sent, size);
        }
    }

    if(len == size) sent = realloc(sent,size+1);

    sent[len] = '\0';
    return sent;
}

char* clear(char* sent){
    while (sent[0] == ' ' || sent[0] == '\t' || sent[0] == '\n'){
        int i;

        for(i = 0; i < strlen(sent) - 1; i++) sent[i] = sent[i+1];

        sent[i] = '\0';
    }
    return sent;
}

int del(char* sent){
    for(int i = 0; i < strlen(sent) - 1; i++) if (sent[i] == '7') return 0;
    return 1;
}

int main() {
    int real_sent_amount = 0;
    int del_sent = 0;
    int sent_amount = 50;
    char* last_sent = "Dragon flew away!";
    char** text = malloc(sizeof(char*) * sent_amount);
    char* sent;

    while (1) {
        sent = clear(input());

        if (del(sent)) text[real_sent_amount++] = sent;

        else del_sent += 1;

        if (real_sent_amount == sent_amount) {
            sent_amount += 100;
            text = realloc(text, sent_amount * sizeof(char*));
        }

        if (!strcmp(sent, last_sent)) break;
    }

    for (int i = 0; i < real_sent_amount; i++) printf("%s\n", text[i]);

    free(text);
    sent_amount = real_sent_amount + del_sent - 1;
    real_sent_amount = real_sent_amount - 1;
    printf("Количество предложений до %d и количество предложений после %d\n", sent_amount,  real_sent_amount);
    return 0;
}