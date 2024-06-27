#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define END_OF_SENTENCE '\0'
#define END_OF_TEXT "Dragon flew away!"
#define BUF_SIZE 10

char * get_sentence();
char ** get_text(int * size);
bool contains_555(char * sentence);
void print_result(char ** text, int * size);

int main(){
    int size = 0;
    char ** start_text = get_text(&size);
    print_result(start_text, &size);
    return 0;
}

char * get_sentence(){
    char symbol;
    int size = 0;
    int curr_buf = BUF_SIZE;
    char * sentence = malloc(BUF_SIZE);

    do {
        symbol = getchar();
        if (size == 0 && isspace(symbol)){
            continue;
        }
        else {
            sentence[size++] = symbol;
            if (size == curr_buf - 1){
                curr_buf += BUF_SIZE;
                sentence = realloc(sentence, curr_buf);
            }
        }
    } while (symbol != '.' && symbol != ';' && symbol != '?' && symbol != '!');

    sentence[size] = END_OF_SENTENCE;
    return sentence;
}

char ** get_text(int * size){
    int curr_size = BUF_SIZE;
    char * curr_sentence;
    char ** text = malloc(curr_size * sizeof(char * ));
    
    do {
        curr_sentence = get_sentence();
        text[(*size)++] = curr_sentence;
        if ( (*size) == curr_size - 1){
            curr_size += BUF_SIZE;
            text = realloc(text, curr_size * sizeof(char *));
        }
        
    } while (strcmp(curr_sentence, END_OF_TEXT) != 0); // strcmp возвращает 0, если две строки совпадают
    return text;
}

bool contains_triple_five(char * sentence){
    bool case_one = strstr(sentence, " 555 ") != NULL; // strstr возвращает NULL, если подстроки нет в строке
    bool case_two = strstr(sentence, " 555.") != NULL;
    bool case_three = strstr(sentence, " 555;") != NULL;
    bool case_four = strstr(sentence, " 555?") != NULL;
    bool case_five = strstr(sentence, "555 ") != NULL;

    if (case_one || case_two || case_three || case_four || case_five){
        return true;
    }

    return false;
}

void print_result(char ** text, int * size){
    int start_size = (*size);
    int final_size = 0;
    for (int i = 0; i < start_size; i++){
        if (contains_triple_five(text[i]) == false){
            printf("%s\n", text[i]);
            final_size++;
        }
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d", start_size - 1, final_size - 1);
}
