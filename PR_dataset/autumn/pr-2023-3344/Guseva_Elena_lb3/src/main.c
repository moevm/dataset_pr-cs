#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void erase(char *line){
    if(line[0]=='\t' || line[0]==' '){
        memmove(line, line+1, strlen(line));
        erase(line);
    }
}

int is_555(char *sentence){
    int len = strlen(sentence);
    for (int i = 0; i < len-4; i++) {
        if (((strchr("\n\t", sentence[i]) || (sentence[i] == ' ')) && sentence[i+1] == '5' && sentence[i+2] == '5' && sentence[i+3] == '5' && (strchr("\n\t.;? ", sentence[i+4]) || sentence[i+4] == '\0')) || (sentence[i] == '5' && sentence[i+1] == '5' && sentence[i+2] == '5') && sentence[i+3] == ' ') {
            return 1;
        }
    }
    return 0;
}

void removeNewLines(char *str) {
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != '\n') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(){
    char **result = malloc(1 * sizeof(char*));
    char *line = malloc(1 * sizeof(char));
    int count = 0;
    int new_count = 0;
    int letter_count = 0;
    char letter;

    while (1) {
        new_count++;
        free(line);
        line = malloc(1 * sizeof(char));
        letter = '1';

        while (letter != '.' && letter != ';' && letter != '?' && letter != '!') {
            if (letter == '\n') {
                letter = ' ';
            }
            letter = getchar();
            line[letter_count] = letter;
            letter_count++;
            line = realloc(line, sizeof(char) * letter_count + 1);
        }
        line[letter_count] = '\0';

        result = realloc(result, (new_count + 1) * sizeof(char*));
        result[new_count - 1] = line;
        count++;

        if (strstr(line, "Dragon flew away!")) {
            break;
        }

        letter_count = 0;
        line = malloc(1 * sizeof(char));


    }

    new_count=0;

    for(int i=0; i<count; i++){
        erase(result[i]);
        if (!is_555 (result[i])){
            removeNewLines(result[i]);
            printf("%s\n",result[i]);
            new_count++;
        }
    }

    printf("Количество предложений до %d и количество предложений после %d\n", count - 1, new_count - 1);
    for(int i=0; i<count; i++) {
        free(result[i]);
    }
    free(result);
    return 0;
}
