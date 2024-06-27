#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_final_sentence(char str[]) {
    return !strncmp(str, "Dragon flew away!", 17);
}

void skip_space() {
    char c;
    do c = getchar(); while (isspace(c));
    ungetc(c, stdin);
}

void read_sentence(char str[]) {
    skip_space();
    char* p;
    for (p = str; ; ++p) {
        *p = getchar();
        if (*p == '.' || *p == ';' || *p =='?') break;
        if (*p == '!' && is_final_sentence(str)) break;
    }
    *++p = '\0';
}

int has_digit_inside_word(char str[]) {
    for (++str; *str; ++str)
        if (isdigit(*str) && (
            isalpha(*(str-1)) && isalnum(*(str+1))
            || isalpha(*(str+1)) && isalnum(*(str-1))
        )) return 1;
    return 0;
}

int main() {
    char* sentence = (char*)malloc(128);
    int in_sentences = 0, out_sentences = 0;
    do {
        read_sentence(sentence);
        if (!has_digit_inside_word(sentence)) {
            puts(sentence);
            ++out_sentences;
        }
        ++in_sentences;
    } while (!is_final_sentence(sentence));
    printf(
        "Количество предложений до %d и количество предложений после %d",
        in_sentences - 1, out_sentences - 1
    );
    free(sentence);
}
