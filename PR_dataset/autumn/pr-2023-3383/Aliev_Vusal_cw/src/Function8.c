#include "Common.h"
#include "Function8.h"

void Function8(char** text, int* count_sent){
    char* sent = text[0];
    char* rasd = malloc(sizeof(char) * strlen(text[0]));

    int l = 0;
    for (; sent[l] != '\0'; l++){
        rasd[l] = sent[l];

        if (sent[l] == '\n'){
            rasd[l] = '\0';
            l++;
            break;
        }
    
    }
    int j = 0;
    for (; text[0][j] != '\0'; j++){
        text[0][j] = sent[l];
        l++;
    }
    j++;
    text[0][j] = '\0';

    int N = 0;
    for (int k = 0; text[k] != NULL; k++){
        text[k][strlen(text[k])-1] = '\0';
        N++;

    }
    
    int p = N;
    if (N % 2 == 0){
        for (int i = 0; i != N; i++){
            printf("%s %s %s.\n", text[i], rasd, text[N-1]);
            N--;
        }  
    }
    else{
        for (int i = 0; i != (N/2)+1; i++){
            printf("%s %s %s.\n", text[i], rasd, text[p-1]);
            p--;
    }
    free(rasd);
    }
}