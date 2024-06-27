#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int end_sentence(int symbol) {
    return strchr(".;?!", symbol) != NULL;
}

int uppers(char* text) {
    int count = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z'){
            count++;
        }
        if (count > 1) return 1;
    }
    return 0;
}

char* delete_space_or_tab(char* str) {
    if ((str[0] == ' ') || (str[0]) == '\t') memmove(str, str + 1, strlen(str));
    return str;
}

int main() {
    char** text = (char**)malloc(sizeof(char*));
    int all_text, right_text = 0;
    int moevm = 0;
    while (1) {
        char* sentence = (char*)malloc(sizeof(char));
        char symbol = 1;
        int count_symbol = 0;

        while (!end_sentence(symbol)) {
            symbol = getchar();
            if (symbol == '\n') symbol = ' ';
            sentence[count_symbol++] = symbol;
            sentence = realloc(sentence, sizeof(char) * (count_symbol + 1));
        }

        all_text++;
        sentence[count_symbol] = '\n';
        count_symbol++;
        sentence = realloc(sentence, sizeof(char) * (count_symbol + 1));
        sentence[count_symbol] = '\0';

        if (!uppers(sentence)) {
            text [right_text++] = sentence;
            text = realloc(text, sizeof(char *) * (right_text + 1));

            if (strstr(sentence, "Dragon flew away!")) break;

        }else free(sentence);

    }
    for (int i = 0; i < right_text; i++) {
        printf("%s", delete_space_or_tab(text[i]));
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d\n", all_text - 1, right_text - 1);
    return 0;
}
