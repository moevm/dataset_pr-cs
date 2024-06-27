#include <stdio.h>
#include <stdlib.h>

#define SIZE_TEXT_END  17
#define END_TEXT "Dragon flew away!"
#define FALSE 0
#define TRUE 1

int check_end(const char *text) {
    for (int i = 0; i < SIZE_TEXT_END; ++i) {
        if (text[i] != END_TEXT[i]) {
            return 0;
        }
    }

    return 1;
}

int check_end_sentence(const char symbol) {
    if (symbol == '!' || symbol == '.' || symbol == '?' || symbol == ';')
        return 1;
    else
        return 0;
}

int is_right_sentence(const char *text, int size_sentence) {
    int count_five = 0;
    int index_start_five = 0;

    for (int i = 0; i < size_sentence - 1; ++i) {
        if (text[i] == '5') {
            if (count_five == 0) {
                index_start_five = i;
            }

            count_five++;

            if (count_five == 3) {
                if (index_start_five == 0) {
                    if (text[index_start_five + 3] == ' ') {
                        return 0;
                    }
                } else if (index_start_five == (size_sentence - 4)) {
                    if (text[index_start_five - 1] == ' ') {
                        return 0;
                    }
                    
                } else if (text[index_start_five - 1] == ' ' && text[index_start_five + 3] == ' ') {
                    return 0;
                }
            }
        } else {
            count_five = 0;
        }
    }

    return 1;
}

void print_sentence(const char *text, int size_sentence) {
    for (int i = 0; i < size_sentence; ++i) {
        printf("%c", text[i]);
    }
    printf("\n");
}

void print_result(const int n, const int m) {
    printf("Количество предложений до %d и количество предложений после %d", n, m);
}

int main()
{
    int symbol;
    int n = -1;
    int m = -1;

    char *text = malloc(sizeof(char));
    int size_sentence = 1;
    int sentence_start = FALSE;

    while ((symbol = getchar()) != EOF) {
        if (!sentence_start) {
            if (symbol != '\t' && symbol != ' ') {
                text[0] = symbol;
                sentence_start = TRUE;
            } else {
                continue;
            }
        } else {
            size_sentence++;
            text = realloc(text, size_sentence * sizeof(char));

            text[size_sentence - 1] = symbol;

            if (check_end_sentence(symbol)) {
                n++;

                if (is_right_sentence(text, size_sentence)) {
                    m++;

                    print_sentence(text, size_sentence);

                    if (size_sentence == SIZE_TEXT_END && check_end(text)) {
                        print_result(n, m);
                    }
                }

                free(text);
                text = malloc(sizeof(char));
                size_sentence = 1;
                sentence_start = FALSE;
            } else {

            }
        }
    }

    free(text);

    return 0;
}