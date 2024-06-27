#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SENTENCE_SIZE 150
#define LAST_SENTENCE "Dragon flew away!"
void data_input(int* before_count, int* after_count){
    char* sentence = (char*)malloc(SENTENCE_SIZE*sizeof(char));
    char letter;
    int index = 0;
    int size_sentence = SENTENCE_SIZE;
    while(strcmp(sentence,LAST_SENTENCE)){
        if (index == size_sentence-1){
            size_sentence += SENTENCE_SIZE;
            sentence = (char*)realloc(sentence, size_sentence*sizeof(char));
        }
        letter = getchar();
        if((index==0) && ((letter==' ')||(letter=='\t')))
                continue;
        else{
            sentence[index] = letter;
            index++;
            if ((letter== '.') || (letter == ';')){
                sentence[index]='\0';
                printf("%s\n", sentence);
                free(sentence);
                sentence = (char*)calloc(size_sentence, sizeof(char));
                *before_count+=1;
                *after_count+=1;
                index = 0;
            }
            if(sentence[strlen(sentence)-1] == '?'){
                *before_count+=1;
                index = 0;
                free(sentence);
                sentence = (char*)calloc(size_sentence,sizeof(char));
                
            }
        }
    }
    free(sentence);
    printf(LAST_SENTENCE);
    printf("\n");
}
int main(){
    int before_count = 0, after_count = 0;
    data_input(&before_count, &after_count);
    printf("Количество предложений до %d и количество предложений после %d", before_count, after_count);
    return 0;
}