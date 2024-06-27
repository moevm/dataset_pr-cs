#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define START_SIZE 100

int main() {
    char *sntns;
    int size = START_SIZE;
    sntns = (char *)malloc(START_SIZE);
    int st = -1;
    int fin = -1;
    int len_s = 1;
    char *test;
    char c;
    int line = 1;
    int step=10;
    int fl=1;
    do {
        do{
            c = getchar();
            if (c=='7') fl = 0;
            if (c=='\n') continue;
            if (isblank(c) && len_s==1) continue;
            if (len_s<=size) {
                sntns[len_s-1]=c;
                sntns[len_s]='\0';
                len_s++;
            } else {
                test = (char *)realloc(sntns, (size+step)*sizeof(char));
                size += step;
                if (test!=NULL){
                    sntns=test;
                    sntns[len_s-1]=c;
                    sntns[len_s]='\0';
                    len_s++;
                }
                else {
                    printf("Ошибка выделения памяти.");
                    return -1;

                }
            }
            if (c=='.' || c==';' || c=='?' || c=='!') break;

        }while (1);
        if (fl==0) {
            st++;
            sntns[0]='\0';
            len_s=1;
            size=START_SIZE;
            fl = 1;

        } else {
            st++;
            fin++;
            printf("%s\n", sntns);
            if (strcmp(sntns, "Dragon flew away!")==0) break;
            sntns[0]='\0';
            len_s=1;
            size=START_SIZE;
        }
    } while(1);
    free(sntns);
    printf("Количество предложений до %d и количество предложений после %d", st, fin);
    return 0;
}
