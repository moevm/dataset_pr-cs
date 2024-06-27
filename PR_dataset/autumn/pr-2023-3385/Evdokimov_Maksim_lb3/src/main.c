#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BLOCK 50

char** append_str(char** m, int* cap, int last, char* c) {
    if (last >= *cap) {
        *cap = *cap + BLOCK;
        m = realloc(m, *cap * sizeof(char*));
        if (m == NULL) {
            exit(1);
        }
    }
    m[last] = c;
    return m;
}

char* append_chr(char* m, int* cap, int last, char c) {
    if (last >= *cap) {
        *cap = *cap + BLOCK;
        m = realloc(m, *cap * sizeof(char));
        if (m == NULL) {
            exit(1);
        }
    }
    m[last] = c;
    return m;
}


int main()
{
    char** sentences = malloc(BLOCK * sizeof(char*));
    int cap = BLOCK;
    int last = 0;
    
    char* cur_sentence = malloc(BLOCK * sizeof(char));
    int cur_cap = BLOCK;
    int cur_last = 0;
    int upper_counter = 0;
    
    int raw_counter = 0;
    while(1) {
        char c = getchar();
        
        if (cur_last == 0 && isspace(c)) {
            continue;
        }
        if (isupper(c)) {
            upper_counter++;
        }
        cur_sentence = append_chr(cur_sentence, &cur_cap, cur_last++, c);
        if (c == '.' || c == ';' || c == '?' || c == '!') {
            raw_counter++;
            cur_sentence = append_chr(cur_sentence, &cur_cap, cur_last++, '\0');
            if (upper_counter <= 1) {
                sentences = append_str(sentences, &cap, last++, cur_sentence);
            }
			else {
				free(cur_sentence);
			}
            cur_last = 0;
            cur_sentence = malloc(BLOCK * sizeof(char));
            cur_cap = BLOCK;
            upper_counter = 0;
            
            if (c == '!') {
                break;
            }
        }
    }
    for (int i = 0; i < last; i++) {
        for (int j = 0; j < strlen(sentences[i]); j++) {
            printf("%c", sentences[i][j]);
        }
        printf("\n");
    }
    printf("Количество предложений до %d и количество предложений после %d",raw_counter-1, last-1);
}
