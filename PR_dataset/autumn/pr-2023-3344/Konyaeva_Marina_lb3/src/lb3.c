#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int Diginword(char *word) {
    int first, last;
    int flag = 0;
    for (int i = 0; i < strlen(word); i++) {
        if (isalpha(word[i]) != 0) {
            first = i;
            break;
        }
        if (i == strlen(word) - 1) {
            return 0;
        }
    }
    for (int j = strlen(word); j > 0;j--) {
        if (isalpha(word[j]) != 0) {
            last = j;
            break;
        }
    }
    for (int i = first; i < last; i++) {
        if (isdigit(word[i]) != 0) {
            flag = 1;
            return 1;
        }
    }
    return 0;
}

int SplitSentence(char *sentence) {

    char sep[] = " ";
    char *word = strtok(sentence, sep);
    while (word != NULL) {
        if(Diginword(word))
            return 1;
        word = strtok(NULL,sep);
    }
    return 0;
}

void format(char *sentence){
    for (int i = 0;i < strlen(sentence);i++){
        if(sentence[i]=='\t')
            sentence[i]=' ';
    }
    if(sentence[0]==' ')
        memmove(sentence,sentence+1,strlen(sentence));
}


int main() {
    char **text = (char **) malloc(1 * sizeof(char *));
    char *sentence = malloc(1 * sizeof(char));
    int count = 0;
    int all_count = 0;
    char symbol;
    while (1) {
        int symbol_count = 0;
        do {
            symbol = getchar();
            sentence[symbol_count] = symbol;
            symbol_count++;
            sentence = realloc(sentence, (symbol_count + 1) * sizeof(char));
        } while (symbol != '.' && symbol != ';' && symbol != '!' && symbol != '?');
        sentence[symbol_count++] = '\0';
        char *temp = (char*)malloc(symbol_count*sizeof(char));
        strcpy(temp,sentence);
        if (SplitSentence(temp) ==0) {
            format(sentence);
            text[count] = sentence;
            count++;
            text = realloc(text, (count + 1) * sizeof(char *));
        }
        if (strstr(sentence, "Dragon flew away!"))
            break;
        all_count++;
        sentence = malloc(1 * sizeof(char));
    }
    for (int i = 0; i < count; i++) {
        printf("%s\n", text[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d", all_count, count-1);
    free(sentence);
    free(text);
    return 0;
}
