#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
    char **arrofsent = malloc(sizeof(char*));
    unsigned countBefore = 0, countAfter = 0;

    while(1){
        countBefore++;
        char *sent = malloc(sizeof(char));
        unsigned chrCount = 0;
        char ch = 'c';

        while (ch != '.' && ch != ';' && ch !='?' && ch != '!'){
            ch = getchar();
            sent[chrCount] = ch;
            chrCount++;
            sent = realloc(sent, (chrCount + 1) * sizeof(char));
        }
        sent[chrCount] = '\0';

        if (sent[0] == ' ' || sent[0] == '\n') {
            memmove(sent, sent+ 1, strlen(sent));
        }

        if (strchr(sent,'7') == NULL){
            arrofsent[countAfter] = sent;
            countAfter++;
            arrofsent = realloc(arrofsent, (countAfter + 1) * sizeof(char*));
        }

        if (strstr(sent, "Dragon flew away")) {
            break;
        }
    }

  for (int i = 0; i < countAfter; i++) {
        printf("%s\n", arrofsent[i]);
        free(arrofsent[i]);
  }
  free(arrofsent);
  printf("Количество предложений до %d и количество предложений после %d\n",countBefore-1, countAfter-1);
  return 0;
}
