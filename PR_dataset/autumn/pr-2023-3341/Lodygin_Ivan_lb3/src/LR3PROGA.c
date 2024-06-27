#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* input(int*, int*);
void output(char*, int*, char*);
void get_punctuation(char*, char*);
int check(char*);

int main() {
    int text_size = 0;
    int rows_before = 0;
    char* text = input(&text_size, &rows_before);
    char punctuation[rows_before+1];
    get_punctuation(text, punctuation);
    output(text, &rows_before, punctuation);
    return 0;
}

char* input(int* text_size, int* rows_before) {
    char* text = (char*)malloc((*text_size + 10000) * sizeof(char));
    char symbol = 0;
    int i = 0;
    while (symbol != '!') {
        symbol = getchar();
        if(symbol != '\t' && symbol != '\n') {
            if (symbol == '!' || symbol == '.' || symbol == ';' || symbol == '?') (*rows_before)++;
            text[i] = symbol;
            (*text_size)++;
            i++;
        }
    }
    return text;
}

void get_punctuation(char* text, char* punctuation) {
    int j = 0;
    for (int i=0; i<strlen(text); i++) {
        if (text[i] == '!' || text[i] == '.' || text[i] == ';' || text[i] == '?') {
            punctuation[j] = text[i];
            j++;
        }
    }
}

void output(char* text, int* rows, char* punctuation) {
    int rows_before = *rows;
    char* separators = ".;?";
    char* substr;
    int i = 0;
    substr = strtok(text, separators);
    while (substr != NULL) {
        if (check(substr)) {
            int checkbox = 0;
            for (int q = 0; q<strlen(substr); q++) {
                if (substr[q] != ' ') checkbox = 1;
                if (checkbox) {
                    printf("%c", substr[q]);
                }
            }
            if (i != rows_before-1) {
                printf("%c", punctuation[i]);
            }
            printf("\n");
        } else {
            (*rows)--;
        }
        substr = strtok(NULL, separators);
        i++;
    }
    printf("Количество предложений до %d и количество предложений после %d\n", rows_before-1, *rows-1);
}

int check(char* sent) {
    for (int i=1; i<strlen(sent)-2; i++) {
        if (sent[i-1] == ' ' && sent[i] == '5' && sent[i+1] == '5' && sent[i+2] == '5' && sent[i+3] == ' ') return 0;
    }
    if (strlen(sent) >= 4) {
        if (sent[0] == '5' && sent[1] == '5' && sent[2] == '5' && (sent[3] == ' ')) return 0;
        if (sent[strlen(sent)-4] == ' ' && sent[strlen(sent)-3] == '5' && sent[strlen(sent)-2] == '5' && sent[strlen(sent)-1] == '5') return 0;
    }
    return 1;
}