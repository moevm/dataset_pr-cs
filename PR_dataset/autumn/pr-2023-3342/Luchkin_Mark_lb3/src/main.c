#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **get_text(int *len_before);
int is_number(char *word);
int has_digits(char *sentence);
void output(char **text, int len_before);


int main(){
    int len_before = 0; 
    char **text = get_text(&len_before);
    output(text, len_before);

    for (int i = 0; i < len_before; i++) {
        free(text[i]);
    }

    free(text);
    return 0;
}

char **get_text(int *len_before){
    int text_capacity = 1;
    int sentence_capacity = 1; 
    int sentence_len = 0; 
    char curr_char; 

    char *sentence_from_chars = malloc(sizeof(char) * sentence_capacity); 
    char **text = malloc(sizeof(char*) * text_capacity); 

    do{
        curr_char = getchar();
        if (curr_char == '\n'){
            continue; 
        }

        sentence_from_chars[sentence_len++] = curr_char;
        if (sentence_capacity <= sentence_len){
            sentence_capacity *= 2;
            sentence_from_chars = realloc(sentence_from_chars, sizeof(char) * sentence_capacity);
        }

        if (curr_char == '.' || curr_char == ';' || curr_char == '?' || curr_char == '!'){
            sentence_from_chars[sentence_len] = '\0';
            if (sentence_from_chars[0] == ' '){
                memmove(sentence_from_chars, sentence_from_chars + 1, strlen(sentence_from_chars));
            }

            text[(*len_before)++] = strdup(sentence_from_chars);
            sentence_capacity = 1;
            sentence_len = 0;
            if (text_capacity <= (*len_before)){
                text_capacity *= 2;
                text = realloc(text, sizeof(char*) * text_capacity);
            }

        }

    } while (curr_char != '!');

    return text;
}

int is_number(char *word){
    int len = strlen(word);
    for (int i = 0; i < len; i++){
        if (isdigit(word[i])){
            continue;
        }
        return 0;
    }
    
    return 1;
}

int has_digits(char *sentence){
    const char *sep = " .;?!";
    char *word = strtok( strdup(sentence), sep);
    
    while (word != NULL){
        if (is_number(word)){
            word = strtok(NULL, sep);
            continue;
        }
        for (int i = 1; i < strlen(word) - 1; i++){
            if (isdigit(word[i])){
                return 1;
            }
        }

        word = strtok(NULL, sep);
    } 

    return 0;
}

void output(char **text, int len_before){
    int len_after = 0; 
    char *sentence;
    for (int i = 0; i < len_before; i ++){
        sentence = text[i];
        if (has_digits(sentence) == 0){
            printf("%s\n", sentence);
            len_after++;
        }
    }

    printf("Количество предложений до %d и количество предложений после %d", len_before - 1, len_after - 1);
}
