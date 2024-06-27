#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ADD_SIZE 30
#define MAX_SIZE 100


int check(char *s) {
    int flag = 1;
    for (int i = 0; s[i]; i++) {
        if (isdigit(s[i])) {
            if (isalpha(s[i - 1]) && s[i + 1] != ' ' && s[i + 1] != '.' && s[i + 1] != ';' && s[i + 1] != '?') {
                flag = 0;
            }
        }
    }
    return flag;
}

int main() {
    int current_size = MAX_SIZE, counter = 0, answer1 = 0, answer2 = 0;
    char *text = malloc(sizeof(char) * current_size);
    char c = getchar();
    while (c != '!') {
        if (counter + 1 >= current_size) {
            char *s = (char *) realloc(text, sizeof(char) * (current_size + ADD_SIZE));
            if (s != NULL) {
                text = s;
                current_size += ADD_SIZE;
            }
        }
        if ((c == ' ' || c == '\t') && (counter == 0) || ((c == '\n') && (counter == 0))) {
            c = getchar();
            continue;
        }
        text[counter] = c;
        counter++;
        if (c == '.' || c == ';' || c == '?') {
            text[counter] = '\0';
            if (check(text)) {
                printf("%s\n", text);
                answer2++;
            }
            answer1++;
            counter = 0;
            free(text);
            text = (char *) calloc(current_size, sizeof(char));
        }
        c = getchar();
    }
    printf("Dragon flew away!\nКоличество предложений до %d и количество предложений после %d", answer1, answer2);
    return 0;
}