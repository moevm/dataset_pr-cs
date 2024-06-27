#include <stdio.h>
#include <string.h>

#define MAX_TEXT 100000

void print_sentences(char *text) {
    char *start = text;
    char *end;
    int n = 0;
    int m = 0;

    while ((end = strpbrk(start, ".;?")) != NULL) {
        if (*end != '?') {
            char *temp = start;
            while (temp <= end && (*temp == ' ' || *temp == '\t')) {
                temp++;
            }

            while (temp <= end) {
                putchar(*temp++);
            }
            putchar('\n');
            m++;
        }
        start = end + 1;
        n++;
    }
    printf("%s\n","Dragon flew away!");
    printf("Количество предложений до %d и количество предложений после %d", n, m);
}

int main() {
    char text[MAX_TEXT];
    fgets(text, MAX_TEXT, stdin);
    print_sentences(text);
    return 0;
}

