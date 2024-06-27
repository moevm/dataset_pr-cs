#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//char str[]="Dragon flew away!";

int main()
{
    int* sizes_of_sentences=malloc(sizeof(int)*1);
    int amount_of_sizes=0;
    char** sentences=malloc(sizeof(char*)*1);
    sentences[0]=malloc(sizeof(char)*1);
    char letter=getchar();
    int amount_of_letters=0;
    int amount_of_sentences=0;
    while (1){
        if (amount_of_letters==0 && (letter==' ' || /*letter=='\0' ||*/ letter=='\n' || letter=='\t')){
            letter=getchar();
            continue;
        }
        sentences[amount_of_sentences]=realloc(sentences[amount_of_sentences],  (amount_of_letters+1)* sizeof(char));
        sentences[amount_of_sentences][amount_of_letters]=letter;
        amount_of_letters++;
        
        if (letter=='!'){
            sentences[amount_of_sentences]=realloc(sentences[amount_of_sentences],  (amount_of_letters+1)* sizeof(char));
            sentences[amount_of_sentences][amount_of_letters]='\0';
            amount_of_sentences++;
            break;
        }
        
        if (letter=='.' || letter==';' || letter=='?'){
            sentences[amount_of_sentences]=realloc(sentences[amount_of_sentences],  (amount_of_letters+1)* sizeof(char));
            sentences[amount_of_sentences][amount_of_letters]='\0';
            sizes_of_sentences[amount_of_sizes]=amount_of_letters;
            amount_of_sizes++;
            sizes_of_sentences=realloc(sizes_of_sentences,sizeof(int)*(amount_of_sizes+1));
            amount_of_letters=0;
            amount_of_sentences++;
            sentences=realloc(sentences,sizeof(char*)*(amount_of_sentences+1));
            sentences[amount_of_sentences]=malloc(sizeof(char)*1);
        }
        letter=getchar();
    }
    int x=0;
    int amount_of_right_sentences=amount_of_sentences;
    for (int i=0;i<amount_of_sentences;i++){
        for (int j=0;j<sizes_of_sentences[i]-3;j++){
            if (sentences[i][j]=='5' && sentences[i][j+1]=='5' && sentences[i][j+2]=='5'){
                if ((j==0 || isalnum(sentences[i][j-1])==0) && isalnum(sentences[i][j+3])==0){
                    x=1;
                }
            }
        }
        if (x==0){
            puts(sentences[i]);
        }
        else{
            x=0;
            amount_of_right_sentences--;
        }
    }
    
    for (int i=0; i<amount_of_sentences; i++){
        free(sentences[i]);
    }
    free(sentences);
    
    printf("Количество предложений до %d и количество предложений после %d", amount_of_sentences-1, amount_of_right_sentences-1);
    return 0;
}