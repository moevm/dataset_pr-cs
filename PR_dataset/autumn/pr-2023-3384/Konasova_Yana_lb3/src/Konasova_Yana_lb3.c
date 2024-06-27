#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MASSIV 100
#define STEP 20

int main() {
    int start_amount = 0;
    int end_amount = 0;
    int len_sentence = 0;
    char *sent;
    int size_sent = MASSIV;
    char a;
    int yes_or_no = 1;

    sent = (char *)malloc(MASSIV);

    do {
        do{
            a = getchar();

            if (a == '\n') {
                continue;
            }

            if (isblank(a) && len_sentence==0) continue;

            if (a == '7') {
                yes_or_no = 0;
            }
            if (a == '.' || a == ';' || a == '?' || a == '!') {
                sent[len_sentence] = a;
                sent[len_sentence+1] = '\0';
                len_sentence++;
                break;
            }

            if (len_sentence < size_sent) {
                sent[len_sentence] = a;
                sent[len_sentence+1] = '\0';
                len_sentence++;
            } else {
                size_sent = size_sent + STEP;
                sent = (char *)realloc(sent, size_sent * sizeof(char));
                sent[len_sentence] = a;
                sent[len_sentence+1] = '\0';
                len_sentence++;
            }
        }while(1);

        if (!yes_or_no) {
            start_amount++;
            size_sent = MASSIV;
            len_sentence = 0;
            sent[0]='\0';
            yes_or_no = 1;
            
        }else{
            printf("%s\n", sent);
            start_amount++;
            end_amount++;
            if (strcmp(sent, "Dragon flew away!")==0) break;
            size_sent = MASSIV;
            len_sentence = 0;
            sent[0]='\0';
        }
        
        
    }while(1);

    printf("Количество предложений до %d и количество предложений после %d", start_amount-1, end_amount-1);
    free(sent);
    return 0;
}
