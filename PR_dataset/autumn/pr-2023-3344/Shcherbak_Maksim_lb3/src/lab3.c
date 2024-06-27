#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int uppers(char* sent);

int main(){
    char** text = malloc(sizeof(char*));
    int first, second = 0;
    int skip = 0;

    do {
        text[second] = (char*)malloc(sizeof(char));

        first = 0;
        char p = 1;

        while (p != '.' && p != ';' && p != '?' && p != '!')
        {
            p = getchar();
            text[second][first++] = p;
            text[second] = realloc(text[second], (first+2)*sizeof(char));
        } 
        text[second][first] = '\0';

        if (uppers(text[second])) {
            skip++;
            continue;
        }
       else{
            if (text[second][0] == '\t' || text[second][0] == ' ') {
                text[second][0] = '\n';
            }
        else if (text[second][0] == '\n' && (text[second][1] == ' ' || text[second][1] == '\t')) {
            memmove(text[second], text[second]+1, first);
            text[second][0] = '\n';
        }
            second++;
            text = realloc(text, sizeof(char*)*(second+1));
       }
    } while ((strstr(text[second-1], "\nDragon flew away!") == 0) && (strstr(text[second-1], "Dragon flew away!") == 0));

    for (int i = 0; i < second; i++) {
        printf("%s", text[i]);
        free(text[i]);
    }
    free(text);
    printf("\nКоличество предложений до %d и количество предложений после %d\n", second+skip-1, second-1);
    return 0;
}
int uppers(char* byk) {
    int count = 0;
    for (int i = 0; i < strlen(byk); i++) {
        if (byk[i] >= 'A' && byk[i] <= 'Z') {
            count++;
        }

        if(count > 1) return 1;
    }
    return 0;
}
