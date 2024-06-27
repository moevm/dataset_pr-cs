#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int len=0, ml=100, n=0, t=0,m;
    char *sentence = calloc(100, sizeof(char));
    char symbol;
    while (1){
        symbol = getchar();
        if (symbol == '.' | symbol == ';' |symbol == '?' | symbol == '!'){
            if (len != -1) {
                sentence[len]=symbol;
                len=len+1;
                if (len==ml-2){
                    ml=ml+100;
                    sentence=realloc(sentence, ml *sizeof(char));
                }
                sentence[len] = '\n';
                len=len+1;
                sentence[len] = '\0';
                printf("%s", sentence);
            }
            if (symbol =='!') break;
            n+=1;
            len=0;
        }
        else{
            if ((len== 0 && isblank(symbol)) || len == -1 || symbol == '\n') continue;
            if (symbol == '7') {
                len = -1;
                t += 1;
                continue;
            }
            sentence[len] = symbol;
            len= len+1;
            if (len == ml){
                ml= ml+100;
                sentence=realloc(sentence, ml * sizeof(char));
            }
        }
    }
    m=n-t;
    free(sentence);
    printf("Количество предложений до %d и количество предложений после %d", n, m);
    return 0;
}

