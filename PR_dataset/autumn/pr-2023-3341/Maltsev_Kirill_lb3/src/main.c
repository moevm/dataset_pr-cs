#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* get_text(int*, int*);
void split_text(char*, char**);
void fill_punctuation(char*, char*, int);
void output_sentences(char**, char*, int);
int check_sentence(char*);


int main() {
    int text_size = 1, sentence_count_before = 0;
    char* text = get_text(&text_size, &sentence_count_before);

    char* punctuation = malloc((sentence_count_before+1) * sizeof(char));
    fill_punctuation(text, punctuation, text_size);
    
    char** sentences = malloc((sentence_count_before+1) * sizeof(char*));
    split_text(text, sentences);
    
    output_sentences(sentences, punctuation, sentence_count_before);
    
    return 0;
}


char* get_text(int* text_size, int* sentence_count_before) {
    int capacity = 1;
    char* text = (char*) malloc(sizeof(char));
    char ch = getchar();
    while (ch != '!') {
        text[(*text_size)-1] = ch;
        if ((*text_size) >= capacity) {
            capacity *= 2;
            text = (char*) realloc(text, capacity * sizeof(char));
        }
        (*text_size)++;
        if (ch == '.' || ch == ';' || ch == '?') {
            (*sentence_count_before)++;
        }
        ch = getchar();
    }
    return text;
}


void split_text(char* text, char** sentences) {
    char* sep = ".;?";
    char* substr;
    
    substr = strtok(text, sep);
    int i = 0;
    while (substr != NULL) {
        sentences[i] = substr;
        i++;
        substr = strtok(NULL, sep);
    }
}


void fill_punctuation(char* text, char* punctuation, int text_size) {
    int j = 0;
    for (int i=0; i<text_size-1; i++) {
        if (text[i] == '.' || text[i] == ';' || text[i] == '?') {
            punctuation[j] = text[i];
            j++;
        }
    }
}


void output_sentences(char** sentences, char* punctuation, int sentence_count_before) {
    int sentence_count_after = 0;
    for (int i=0; i<sentence_count_before; i++) {        
        if (check_sentence(sentences[i])) {
            sentence_count_after++;
            int flag = 0;
            for (int j=0; j<strlen(sentences[i]); j++) {
            if (sentences[i][j] != ' ' && sentences[i][j] != '\n')
                flag = 1;
            if (flag && sentences[i][j] != '\n') 
                printf("%c", sentences[i][j]);
        }
        printf("%c\n", punctuation[i]);
        }
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d\n", sentence_count_before, sentence_count_after);
}


int check_sentence(char* sentence) {
    int count_upper = 0;
    for (int i=0; i<strlen(sentence); i++) {
        if (isupper(sentence[i])) count_upper++;
    }
    return (count_upper <= 1);
}
