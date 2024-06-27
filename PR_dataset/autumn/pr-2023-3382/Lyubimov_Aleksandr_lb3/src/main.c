#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    int count_sentence = 0, Max_count = 50, actual_count_sentence = 0;
    int len_sentence = 0, Max_len = 50;
    int delete_sentence = 0;
    char ** text = malloc(sizeof(char*) * Max_count);
    char * sentence = malloc(sizeof(char) * Max_len);
    char letter, prev_letter, prev_prev_letter;
    
    do {
        letter = getchar();
        if (isspace(letter) && len_sentence == 0) {
            continue;
        }
        sentence[len_sentence] = letter;
        
        if (len_sentence > 1) {
            prev_letter = sentence[len_sentence - 1];
            prev_prev_letter = sentence[len_sentence - 2];
            if ((isalpha(prev_prev_letter) || isalpha(letter)) && isdigit(prev_letter) && !(ispunct(letter))) {
                if (!(isdigit(prev_prev_letter) && isdigit(letter) || isspace(prev_prev_letter) || isspace(letter))) {
                    delete_sentence = 1;
                }
            }
        }
        
        if (len_sentence++ >= Max_len - 5) {
            Max_len += 50;
            sentence = realloc(sentence, sizeof(char) * Max_len);
        }

        if (letter == '.' || letter == ';' || letter == '?' || letter == '!') {
            count_sentence ++;
            if (!delete_sentence) {
                sentence[len_sentence] = '\0';
                text[actual_count_sentence] = malloc(sizeof(char) * (len_sentence + 5));
                strcpy(text[actual_count_sentence], sentence);
                if (actual_count_sentence >= Max_count - 5) {
                    Max_count += 50;
                    text = realloc(text, sizeof(char*) * Max_count);
                }
                actual_count_sentence ++;
            }
            free(sentence);
            len_sentence = 0, Max_len = 50, delete_sentence = 0;
            sentence = malloc(sizeof(char) * Max_len);
        }
    } while (letter != '!');
    
    free(sentence);
    for (int i = 0; i < actual_count_sentence; i ++) {
        puts(text[i]);
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d\n", count_sentence - 1, actual_count_sentence - 1);
    return 0;
}