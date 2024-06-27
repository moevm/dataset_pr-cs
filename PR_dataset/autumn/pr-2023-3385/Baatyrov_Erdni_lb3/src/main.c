#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define START_SIZE 100

int main() {
    char *sentence;
    int size = START_SIZE;
    sentence = (char *)malloc(START_SIZE);
    int base_amount = -1;
    int finish_amount = -1;
    int len_s = 1;
    char *test;
    char c;
    int line = 1;
    int step=10;
    int flag=1;
    do {
        do{
            c = getchar();
            if (c=='7') flag = 0;
            if (c=='\n') continue;
            if (isblank(c) && len_s==1) continue;
            if (len_s<=size) {
                sentence[len_s-1]=c;
                sentence[len_s]='\0';
                len_s++;
            } else {
                test = (char *)realloc(sentence, (size+step)*sizeof(char));
                size += step;
                if (test!=NULL){
                    sentence=test;
                    sentence[len_s-1]=c;
                    sentence[len_s]='\0';
                    len_s++;
                }
                else {
                    printf("Ошибка выделения памяти.");
                    return -1;

                }
            }
            if (c=='.' || c==';' || c=='?' || c=='!') break;

        }while (1);
        if (flag==0) {
            base_amount++;
            sentence[0]='\0';
            len_s=1;
            size=START_SIZE;
            flag = 1;

        } else {
            base_amount++;
            finish_amount++;
            printf("%s\n", sentence);
            if (strcmp(sentence, "Dragon flew away!")==0) break;
            sentence[0]='\0';
            len_s=1;
            size=START_SIZE;
        }
    } while(1);
    free(sentence);
    printf("Количество предложений до %d и количество предложений после %d", base_amount, finish_amount);
    return 0;
}

