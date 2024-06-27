#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int many_uppers(char* sent);

int main(){
    char** dragons = malloc(sizeof(char*));
    int let_index, sent_index = 0;
    int skip_count = 0;

    do {
        dragons[sent_index] = (char*)malloc(sizeof(char));
        
        let_index = 0;
        char p = 1;

        while (p != '.' && p != ';' && p != '?' && p != '!')
        {
            p = getchar();
            dragons[sent_index][let_index++] = p;
            dragons[sent_index] = realloc(dragons[sent_index], (let_index+2)*sizeof(char));
        } 
        dragons[sent_index][let_index] = '\0';

        if (many_uppers(dragons[sent_index])) {
            skip_count++;
            continue;
        }
       else{
            if (dragons[sent_index][0] == '\t' || dragons[sent_index][0] == ' ') {
                dragons[sent_index][0] = '\n';
            }
        else if (dragons[sent_index][0] == '\n' && (dragons[sent_index][1] == ' ' || dragons[sent_index][1] == '\t')) {
            memmove(dragons[sent_index], dragons[sent_index]+1, let_index);
            dragons[sent_index][0] = '\n';
        }
            sent_index++;
            dragons = realloc(dragons, sizeof(char*)*(sent_index+1));
       }
    } while ((strstr(dragons[sent_index-1], "\nDragon flew away!") == 0) && (strstr(dragons[sent_index-1], "Dragon flew away!") == 0));
    
    for (int i = 0; i < sent_index; i++) {
        printf("%s", dragons[i]);
        free(dragons[i]);
    }
    printf("\nКоличество предложений до %d и количество предложений после %d\n", sent_index+skip_count-1, sent_index-1);
    return 0;
}

int many_uppers(char* sent) {
    int up_count = 0;
    for (int i = 0; i < strlen(sent); i++) {
        if (sent[i] >= 'A' && sent[i] <= 'Z') {
            up_count++;
        }

        if(up_count > 1) {
            return 1;
        }
    }
    return 0;
}